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

void RadioItemLinker::launchDistributionMessage (QSharedPointer<Message> msg)
{
    qDebug() << "Launch distribution message from Radio Item with ID'" << msg->sourceId() <<"' ";

    if((msg->durationTimeMs() - msg->startSendTime().msecsTo(QTime::currentTime())) <= 0) {
        qDebug() << "Warning: message from Radio Item with ID'" << msg->sourceId() <<"' from the past. Throwing away!";
        return;
    }

    for (auto & neighbor : m_neighbors) {
        if(neighbor.second.second < RadioItem::RADIO_DISTANCE) {
            //neighbor.second.first->
//            if(neighbor.second.first->radioItem()->getParams().rxFreqIndex() == msg->freqIndex()) {

//                        //                QObject::connect(msg.);
//                //QObject::connect(msg->timer(), SIGNAL(timeout()), neighbor.second.first, SLOT(slot()));

//            }
//            else {
//                qDebug() << "Launch distribution message: Radio Item with ID '" << neighbor.first <<"' is on a different frequency";
//            }

        }
        else {
            qDebug() << "Launch distribution message: Radio Item with ID '" << neighbor.first <<"' out of reach";
        }
    }
    //timer->start(1000); // И запустим таймер
}

void RadioItemLinker::launchReceivingMessage(QSharedPointer<Message> msg)
{

}


// -------------------------------------------------- Слоты -----------------------------------------------------

//void RadioItemLinker::slotFinishReceivingMessage(QSharedPointer<Message> msg)
//{
//    if(m_radioItem->getParams().rxFreqIndex() == msg->freqIndex()) {
//        qDebug() << "Finish receiving message: Radio Item with ID '" << m_radioItem->getParams().id()
//                 <<"' successfully received a message from Radio Item  with ID '" << msg->sourceId() <<"'" ;
//    }
//    else {
//        qDebug() << "Finish receiving message: Radio Item with ID '" << m_radioItem->getParams().id() <<"' is on a different frequency";
//    }
//}


