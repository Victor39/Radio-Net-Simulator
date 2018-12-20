#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include "radioitemlinker.h"

RadioItemLinker::RadioItemLinker(std::shared_ptr<RadioItem> radioItem) : m_radioItem(radioItem)
{

}

void RadioItemLinker::addNeighbor(std::shared_ptr<RadioItemLinker> neighbor)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    uint32_t distanceToMe = m_radioItem->getCentrePoint().distance(neighbor->getCentrePoint());
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
        item.second.second = getCentrePoint().distance(item.second.first->getCentrePoint());
    }
}

void RadioItemLinker::updateTopologyFor(const RadioId &radioItemId)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    try
    {
        auto & item = m_neighbors.at(radioItemId);
        item.second = getCentrePoint().distance(item.first->getCentrePoint());
    }
    catch(const std::exception& e){
        qDebug() << "Warning: " << e.what();
    }
}

const Point2D &RadioItemLinker::getCentrePoint() const
{
    return m_radioItem->getCentrePoint();
}

RadioId RadioItemLinker::getId() const
{
    return m_radioItem->getParams().id();
}

void RadioItemLinker::launchReceivingMessage(QSharedPointer<Message> msg)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_radioItem->getParams().rxFreqIndex() == msg->freqIndex()) {

        if (m_receivingMessages.find(msg->freqIndex()) == m_receivingMessages.end()) {
            m_receivingMessages.emplace(msg->freqIndex(), msg);
            int32_t pastTimeMs = msg->startSendTime().msecsTo(QTime::currentTime());
            int32_t remainReceptionTimeMs = msg->durationTimeMs() - (pastTimeMs);
            if(remainReceptionTimeMs > 0) {
                QTimer::singleShot(remainReceptionTimeMs, this, [this, msg] () { this->finishReceivingMessage(msg); });
            }
            else {
                m_receivingMessages.erase(msg->freqIndex());
                qDebug() << "Error of launch receiving message: message receive time has expired";
            }
        }
        else {
            m_receivingMessages.erase(msg->freqIndex());
            qDebug() << "Warning of launch receiving message: message on this frequency is already being received. Discard both messages";
        }
    }
    else {
        qDebug() << "Warning of launch receiving messag: Radio Item with ID '" << m_radioItem->getParams().id() <<"' is on a different frequency. Discard message!";
    }

}

void RadioItemLinker::launchDistributionMessage (QSharedPointer<Message> msg)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    qDebug() << "Launch distribution message from Radio Item with ID'" << msg->sourceId() <<"' ";

    if((msg->durationTimeMs() - msg->startSendTime().msecsTo(QTime::currentTime())) <= 0) {
        qDebug() << "Warning: message from Radio Item with ID'" << msg->sourceId() <<"' from the past. Throwing away message!";
        return;
    }

    for (auto & neighbor : m_neighbors) {
        if(neighbor.second.second <= (RadioItem::RADIO_DISTANCE/2)) {
            neighbor.second.first->launchReceivingMessage(msg);
        }
        else {
            qDebug() << "Launch distribution message: Radio Item with ID '" << neighbor.first <<"' out of reach";
        }
    }
}

void RadioItemLinker::finishReceivingMessage(QSharedPointer<Message> msg)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_radioItem->getParams().rxFreqIndex() == msg->freqIndex()) {
        qDebug() << "End of receiving message: Radio Item with ID '" << m_radioItem->getParams().id() <<
                    "' successfully received a message from Radio Item  with ID '" << msg->sourceId() <<"'";
    }
    else {
        qDebug() << "End of receiving message: Radio Item with ID '" << m_radioItem->getParams().id() <<"' is on a different frequency";
    }

    try {
        m_receivingMessages.erase(msg->freqIndex());
    } catch (const std::exception& e) {
        qDebug() << "Error: " << e.what();
    }
}
