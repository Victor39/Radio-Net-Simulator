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

    void addRadioItem(std::shared_ptr<RadioItem> radioItem);
    bool removeRadioItem(std::shared_ptr<RadioItem> radioItem);
    void updateTopologyFor (const uint32_t & radioItemId);

private:
    ConnectionManager();

    std::unordered_map<uint32_t, std::shared_ptr<RadioItemLinker>> m_radioItemLinkers;

signals:

public slots:
    void slotSendMessage(QSharedPointer<Message> msg);

};

#endif // CONNECTIONMANAGER_H
