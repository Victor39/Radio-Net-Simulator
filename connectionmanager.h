#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <memory>
#include <QGraphicsItem>
#include "radioitem.h"
#include "radioitemlinker.h"
#include "message.h"
#include <QSharedPointer>
#include <unordered_map>


class ConnectionManager : public QObject
{
    Q_OBJECT

public:
    static ConnectionManager & instance();
    virtual ~ConnectionManager();
    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;

    void addRadioItem(RadioItem * radioItem);
    bool removeRadioItemBy(const RadioId & radioItemId);
    const RadioItem * findRadioItemBy(const RadioId & radioItemId) const;
    void updateTopologyFor (const RadioId & radioItemId);
    void getAvailableNeighborsFor (const RadioId & radioItemId, std::list<const RadioItem *> & neighbors) const;

private:
    ConnectionManager();

    std::unordered_map<RadioId, std::shared_ptr<RadioItemLinker>> m_radioItemLinkers;

signals:

public slots:
    void slotSendMessage(QSharedPointer<Message> msg);

};

#endif // CONNECTIONMANAGER_H
