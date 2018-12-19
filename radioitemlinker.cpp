#include <QDebug>
#include "radioitemlinker.h"

RadioItemLinker::RadioItemLinker(std::shared_ptr<RadioItem> radioItem) : m_radioItem(radioItem)
{

}

void RadioItemLinker::addNeighbor(std::shared_ptr<RadioItemLinker> neighbor)
{
    uint32_t distanceToMe = m_radioItem->getCentrePoint().distance(neighbor->getCentrePoint());
    m_neighbors.emplace(neighbor->getId(), std::make_pair(neighbor, distanceToMe));
}

bool RadioItemLinker::removeNeighbor(std::shared_ptr<RadioItemLinker> neighbor)
{
    m_neighbors.erase(neighbor->getId());
    return true;
}

void RadioItemLinker::updateTopologyFor(const RadioId &radioItemId)
{
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
    if(m_radioItem->getParams().rxFreqIndex() == msg->freqIndex()) {

        if ( m_receivingMessages.find(msg->freqIndex()) == m_receivingMessages.end() ) {
            m_receivingMessages.emplace(msg->freqIndex(), msg);
            int32_t pastTimeMs = msg->startSendTime().msecsTo(QTime::currentTime());
            int32_t remainReceptionTimeMs = msg->durationTimeMs() - (pastTimeMs);
            if(remainReceptionTimeMs > 0) {
                QTimer::singleShot(remainReceptionTimeMs, this, [&] () { slotTimerAlarmOfEndReceivedMessage(msg);});
            }
            else {
                m_receivingMessages.erase(msg->freqIndex());
                qDebug() << "Error: Add message to recive: message receive time has expired";
            }
        }
        else {
            m_receivingMessages.erase(msg->freqIndex());
            qDebug() << "Add message to recive: message on this frequency is already being received. Discard both messages";
        }
    }
    else {
        qDebug() << "Add message to recive: Radio Item with ID '" << m_radioItem->getParams().id() <<"' is on a different frequency. Discard message!";
    }

}

void RadioItemLinker::launchDistributionMessage (QSharedPointer<Message> msg)
{
    qDebug() << "Launch distribution message from Radio Item with ID'" << msg->sourceId() <<"' ";

    if((msg->durationTimeMs() - msg->startSendTime().msecsTo(QTime::currentTime())) <= 0) {
        qDebug() << "Warning: message from Radio Item with ID'" << msg->sourceId() <<"' from the past. Throwing away message!";
        return;
    }

    for (auto & neighbor : m_neighbors) {
        if(neighbor.second.second < RadioItem::RADIO_DISTANCE) {
            neighbor.second.first->launchReceivingMessage(msg);
        }
        else {
            qDebug() << "Launch distribution message: Radio Item with ID '" << neighbor.first <<"' out of reach";
        }
    }
}



// -------------------------------------------------- Слоты -----------------------------------------------------

void RadioItemLinker::slotTimerAlarmOfEndReceivedMessage(QSharedPointer<Message> msg)
{
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
