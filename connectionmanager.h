#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QGraphicsItem>
#include <memory>
#include "radioitem.h"
#include "radioitemlinker.h"

class ConnectionManager
{
public:
    static ConnectionManager & instance();
    ~ConnectionManager();
    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;

    void addRadioItem(std::shared_ptr<RadioItem> radioItem);
    bool removeRadioItem(std::shared_ptr<RadioItem> radioItem);
    void updateFor (const uint32_t & radioItemId);


private:
    ConnectionManager();

    std::list<std::shared_ptr<RadioItemLinker>> m_radioItems;

signals:

public slots:
};

#endif // CONNECTIONMANAGER_H
