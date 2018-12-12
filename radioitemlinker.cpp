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

void RadioItemLinker::updateFor(const uint32_t &radioItemId)
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

uint32_t RadioItemLinker::getId() const
{
    return m_radioItem->getParams().id();
}
