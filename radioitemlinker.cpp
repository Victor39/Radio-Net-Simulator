#include <QDebug>
#include <QTimer>
#include "radioitemlinker.h"

RadioItemLinker::RadioItemLinker(RadioItem * radioItem) : m_radioItem(radioItem)
{

}

void RadioItemLinker::addNeighbor(std::shared_ptr<RadioItemLinker> neighbor)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    uint32_t distanceToMe = neighbor->radioItem()->distanceTo(m_radioItem);
    m_neighbors.emplace(neighbor->getId(), std::make_pair(neighbor, distanceToMe));
}

bool RadioItemLinker::removeNeighbor(std::shared_ptr<RadioItemLinker> neighbor)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_neighbors.erase(neighbor->getId());
    return true;
}

void RadioItemLinker::updateTopology()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto & item : m_neighbors) {
        item.second.second = m_radioItem->distanceTo(item.second.first->radioItem());
    }
}

void RadioItemLinker::updateTopologyFor(const RadioId &radioItemId)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    try
    {
        auto & item = m_neighbors.at(radioItemId);
        item.second = m_radioItem->distanceTo(item.first->radioItem());
    }
    catch(const std::exception& e){
        qWarning() << "Warning: " << e.what();
    }
}

RadioId RadioItemLinker::getId() const
{
    return m_radioItem->getParams().id();
}

void RadioItemLinker::launchReceivingMessage(QSharedPointer<Message> msg)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (radioItem()->getParams().mode() == T_RADIO_MODE::RADIO_MODE_OFF) {
        qWarning() << "Warning: Radio Item '" <<getId() << "' can't recive message. Radio Item is OFF";
        return;
    }
    else if (radioItem()->getParams().mode() == T_RADIO_MODE::RADIO_MODE_TX) {
        qWarning() << "Warning: Radio Item '" <<getId() << "' can't recive message. Radio Item is in TRANSMITE mode";
        return;
    }

    if(m_radioItem->getParams().rxFreqIndex() == msg->freqIndex()) {

        if (m_receivingMessages.find(msg->freqIndex()) == m_receivingMessages.end()) {
            QSharedPointer<QTimer> tim = QSharedPointer<QTimer>(new QTimer());
            m_receivingMessages.emplace(msg->freqIndex(), std::make_pair(msg, tim));
            uint32_t rxFreq = msg->freqIndex();
            QObject::connect(m_receivingMessages.at(msg->freqIndex()).second.get(), &QTimer::timeout, this,  [rxFreq, this] (){ this->finishReceivingMessage(rxFreq); });
            int32_t pastTimeMs = msg->startSendTime().msecsTo(QTime::currentTime());
            int32_t remainReceptionTimeMs = msg->durationTimeMs() - (pastTimeMs);
            if(remainReceptionTimeMs > 0) {
                m_receivingMessages.at(msg->freqIndex()).second->start(remainReceptionTimeMs);
            }
            else {
                m_receivingMessages.erase(msg->freqIndex());
                qCritical() << "Error: message receive time has expired";
            }
        }
        else {
            m_receivingMessages.erase(msg->freqIndex());
            qWarning() << "Warning: Radio Item '" << m_radioItem->getParams().id() <<"' is already being received message on this frequency. Discard both messages";
        }
    }
    else {
        qWarning() << "Warning: Radio Item '" << m_radioItem->getParams().id() <<"' is on a different frequency. Discard message from Radio Item '" << msg->sourceId() <<"' !";
    }

}

void RadioItemLinker::launchDistributionMessage (QSharedPointer<Message> msg)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (radioItem()->getParams().mode() == T_RADIO_MODE::RADIO_MODE_OFF) {
        qWarning() << "Warning: Radio Item '" <<getId() << "' can't send message. Radio Item is OFF";
        return;
    }
    else if (radioItem()->getParams().mode() == T_RADIO_MODE::RADIO_MODE_TX) {
        qWarning() << "Warning: Radio Item '" <<getId() << "' can't send message. Another message is already being sent";
        return;
    }

    qInfo() << "Info: sending message from Radio Item '" << msg->sourceId() <<"'";

    if((msg->durationTimeMs() - msg->startSendTime().msecsTo(QTime::currentTime())) <= 0) {
        qWarning() << "Warning: message from Radio Item '" << msg->sourceId() <<"' from the past. Throwing away message!";
        return;
    }

    for (auto & neighbor : m_neighbors) {
        if(neighbor.second.second <= (RadioItem::RADIO_DISTANCE/2)) {
            neighbor.second.first->launchReceivingMessage(msg);
        }
    }
}

void RadioItemLinker::finishReceivingMessage(uint32_t freq)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (radioItem()->getParams().mode() == T_RADIO_MODE::RADIO_MODE_OFF) {
        qWarning() << "Warning: Radio Item '" <<getId() << "' can't finish recive message. Radio Item is OFF";
        m_receivingMessages.erase(freq);
        return;
    }
    else if (radioItem()->getParams().mode() == T_RADIO_MODE::RADIO_MODE_TX) {
        qWarning() << "Warning: Radio Item '" <<getId() << "' can't finish recive message. Radio Item is in TRANSMITE mode";
        m_receivingMessages.erase(freq);
        return;
    }

    try {

        if(m_neighbors.at(m_receivingMessages.at(freq).first->sourceId()).second > (RadioItem::RADIO_DISTANCE/2)) {
            qWarning() << "Warning: Radio Item '" << getId() << "' can't finish recive message. Radio Item is OUT of reach";
            m_receivingMessages.erase(freq);
            return;
        }
    }
    catch (const std::exception& e) {
        qCritical() << "Error: Radio Item '" << getId() << "' can't finish recive message. Problem with source Radio Item!";
        m_receivingMessages.erase(freq);
        return;
    }
    if(m_radioItem->getParams().rxFreqIndex() == freq) {
        qInfo() << "Info: Radio Item '" << m_radioItem->getParams().id() <<
                   "' SUCCESSFULLY received message from Radio Item '" <<  m_receivingMessages.at(freq).first->sourceId() <<"'";
    }
    else {
        qWarning() << "Warning: Radio Item '" << m_radioItem->getParams().id() <<"' did not wait for end of the packet reception and switched to another frequency";
    }

    try {
        m_receivingMessages.erase(freq);
    } catch (const std::exception& e) {
        qCritical() << "Error: " << e.what();
    }
}

const RadioItem *RadioItemLinker::radioItem() const
{
    return m_radioItem;
}

void RadioItemLinker::getAvailableNeighbors(std::list<const RadioItem *> &neighbors) const
{
    for (auto & neighbor : m_neighbors) {
        if(neighbor.second.second <= (RadioItem::RADIO_DISTANCE/2)) {
            neighbors.push_back(neighbor.second.first->radioItem());
        }
    }
}
