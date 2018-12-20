#ifndef RADIOITEMLINKER_H
#define RADIOITEMLINKER_H

#include <unordered_map>
#include <memory>
#include "radioitem.h"
#include <QSharedPointer>
#include "message.h"
#include <QTimer>
#include <thread>
#include <mutex>

class RadioItemLinker : public QObject
{
public:
    explicit RadioItemLinker(std::shared_ptr<RadioItem> radioItem);
    void addNeighbor(std::shared_ptr<RadioItemLinker> neighbor);
    bool removeNeighbor(std::shared_ptr<RadioItemLinker> neighbor);
    void updateTopology();
    void updateTopologyFor(const RadioId & radioItemId);
    const Point2D & getCentrePoint() const;
    RadioId getId() const;
    void launchReceivingMessage (QSharedPointer<Message> msg);
    void launchDistributionMessage (QSharedPointer<Message> msg);
    void finishReceivingMessage(QSharedPointer<Message> msg);

private:
    std::mutex m_mutex;

    std::shared_ptr<RadioItem> m_radioItem;
    std::unordered_map<RadioId, std::pair<std::shared_ptr<RadioItemLinker>, uint32_t>> m_neighbors;

    std::unordered_map<uint32_t, QSharedPointer<Message>> m_receivingMessages;
};

#endif // RADIOITEMLINKER_H
