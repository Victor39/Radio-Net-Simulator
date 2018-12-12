#include "connectionmanager.h"
#include "QDebug"

ConnectionManager & ConnectionManager::instance() {

    static ConnectionManager instance;
    return instance;
}

ConnectionManager::ConnectionManager()
{

}

ConnectionManager::~ConnectionManager()
{

}

void ConnectionManager::addRadioItem(std::shared_ptr<RadioItem> radioItem)
{
    std::shared_ptr<RadioItemLinker> newItemLinker = std::shared_ptr<RadioItemLinker>(new RadioItemLinker(radioItem));

    for(auto & existedItemLinker : m_radioItems) {
        existedItemLinker->addNeighbor(newItemLinker);
    }

    for(auto & existedItemLinker : m_radioItems) {
        newItemLinker->addNeighbor(existedItemLinker);
    }

    m_radioItems.push_back(newItemLinker);
}

bool ConnectionManager::removeRadioItem(std::shared_ptr<RadioItem> radioItem)
{
    uint32_t itemId = radioItem->getParams().id();

    auto foundIter = std::find_if(m_radioItems.begin(), m_radioItems.end(),
                            [itemId](std::shared_ptr<RadioItemLinker> const & m) {
                                return m->getId() == itemId;});

    if(foundIter == m_radioItems.end()) {
        qDebug() << "Warning: item with ID " << itemId << " not found in connection manager!";
        return false;
    }

    m_radioItems.erase(foundIter);

    for (auto & item : m_radioItems) {
        item->removeNeighbor(*foundIter);
    }

    return true;
}

void ConnectionManager::updateFor(const uint32_t & radioItemId)
{
    for (auto & item : m_radioItems) {
        if(item->getId() != radioItemId ) {
            item->updateFor(radioItemId);
        }

    }
}
