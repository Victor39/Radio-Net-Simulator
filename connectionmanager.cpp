#include "connectionmanager.h"
#include "QDebug"

ConnectionManager & ConnectionManager::instance() {

    static ConnectionManager instance;
    return instance;
}

ConnectionManager::ConnectionManager() : QObject()
{
    m_radioItemLinkers.clear();
}

ConnectionManager::~ConnectionManager()
{

}

void ConnectionManager::addRadioItem(std::shared_ptr<RadioItem> radioItem)
{
    std::shared_ptr<RadioItemLinker> newItemLinker = std::shared_ptr<RadioItemLinker>(new RadioItemLinker(radioItem));

    for(auto & existedItemLinker : m_radioItemLinkers) {
        existedItemLinker.second->addNeighbor(newItemLinker);
    }

    for(auto & existedItemLinker : m_radioItemLinkers) {
        newItemLinker->addNeighbor(existedItemLinker.second);
    }

    m_radioItemLinkers.emplace(newItemLinker->getId(), newItemLinker);
}

bool ConnectionManager::removeRadioItem(std::shared_ptr<RadioItem> radioItem)
{
    RadioId itemId = radioItem->getParams().id();

    auto foundIter = std::find_if(m_radioItemLinkers.begin(), m_radioItemLinkers.end(),
                            [itemId](std::pair<uint32_t, std::shared_ptr<RadioItemLinker>> const & m) {
                                return m.first == itemId;});

    if(foundIter == m_radioItemLinkers.end()) {
        qDebug() << "Warning: item with ID " << itemId << " not found in connection manager!";
        return false;
    }

    m_radioItemLinkers.erase(foundIter);

    for (auto & item : m_radioItemLinkers) {
        item.second->removeNeighbor(foundIter->second);
    }

    return true;
}

void ConnectionManager::updateTopologyFor(const uint32_t & radioItemId)
{
    for (auto & item : m_radioItemLinkers) {
        if(item.first != radioItemId ) {
            item.second->updateTopologyFor(radioItemId);
        }
    }
}

// -------------------------------------------------- Слоты -----------------------------------------------------

void ConnectionManager::slotSendMessage(QSharedPointer<Message> msg) {

    try {
        auto sourceLinker =  m_radioItemLinkers.at(msg->sourceId());
        sourceLinker->launchDistributionMessage (msg);
    } catch (const std::exception& e){
        qDebug() << "Error: message from not exist Radio Item with ID " << msg->sourceId() << "; info:" << e.what();
    }
}
