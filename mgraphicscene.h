#ifndef MGRAPHICSCENE_H
#define MGRAPHICSCENE_H

#include <QGraphicsScene>
#include "radioitem.h"

class mGraphicScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit mGraphicScene(QObject *parent = nullptr);

private:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
#ifdef DEBUG_MESSAGE_SEND
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
#endif

signals:
    void sigMouseClick(T_RADIO_PARAM params);
    void sigMouseRelease(const RadioId & radioItemId);

public slots:

};

#endif // MGRAPHICSCENE_H
