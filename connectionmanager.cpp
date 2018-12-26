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

void ConnectionManager::addRadioItem(RadioItem * radioItem)
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

bool ConnectionManager::removeRadioItemBy(const RadioId & radioItemId)
{
    // Находим итератор на удаляемый инстанс
    auto foundIter = std::find_if(m_radioItemLinkers.begin(), m_radioItemLinkers.end(),
                                  [&radioItemId](std::pair<uint32_t, std::shared_ptr<RadioItemLinker>> const & m) {
            return m.first == radioItemId;});

    if(foundIter == m_radioItemLinkers.end()) {
        qWarning() << "Warning: Radio Item '" << radioItemId << "' not found in connection manager!";
        return false;
    }

    // Удаляем соседей из списка
    for (auto & item : m_radioItemLinkers) {
        item.second->removeNeighbor(foundIter->second);
    }

    // Удаляем сам инстанс
    m_radioItemLinkers.erase(foundIter);

    return true;
}

const RadioItem *ConnectionManager::findRadioItemBy(const RadioId &radioItemId) const
{
    // Находим итератор на искомый инстанс
    auto foundIter = std::find_if(m_radioItemLinkers.begin(), m_radioItemLinkers.end(),
                                  [&radioItemId](std::pair<uint32_t, std::shared_ptr<RadioItemLinker>> const & m) {
            return m.first == radioItemId;});

    if(foundIter == m_radioItemLinkers.end()) {
        qWarning() << "Warning: Radio Item '" << radioItemId << "' not found in connection manager!";
        return nullptr;
    }
    return foundIter->second->radioItem();
}

void ConnectionManager::updateTopologyFor(const RadioId & radioItemId)
{
    for (auto & item : m_radioItemLinkers) {
        if(item.first == radioItemId ) {
            item.second->updateTopology();
        }
        else {
            item.second->updateTopologyFor(radioItemId);
        }
    }
}

void ConnectionManager::getAvailableNeighborsFor(const RadioId &radioItemId, std::list<const RadioItem *> & neighbors) const
{
    try {
        auto radioLinker =  m_radioItemLinkers.at(radioItemId);
        radioLinker->getAvailableNeighbors(neighbors);
    } catch (const std::exception& e){
        qCritical() << "Error: not exist Radio Item '" << radioItemId << "' in connection Manager; info:" << e.what();
    }
}

// -------------------------------------------------- Слоты -----------------------------------------------------
void ConnectionManager::slotSendMessage(QSharedPointer<Message> msg) {

    try {
        auto sourceLinker =  m_radioItemLinkers.at(msg->sourceId());
        sourceLinker->launchDistributionMessage (msg);
    } catch (const std::exception& e){
        qCritical() << "Error: message from not exist Radio Item '" << msg->sourceId() << "'; info:" << e.what();
    }
}
