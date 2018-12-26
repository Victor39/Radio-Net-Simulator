#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include "mgraphicscene.h"

mGraphicScene::mGraphicScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

void mGraphicScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    QPointF screenPos = mouseEvent->scenePos();

    if(mouseEvent->button() == Qt::LeftButton) {
        QGraphicsItem * item = itemAt(screenPos, QTransform());
        if(item) {
            emit sigMouseClick(static_cast<RadioItem *>(item)->getParams());
        }
        else {
            T_RADIO_PARAM foo;
            emit sigMouseClick(foo);
        }
    }
    QGraphicsScene::mousePressEvent(mouseEvent);    // Вызываем метод предка, а то не будет двигаться
}

void mGraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent) {

    QPointF screenPos = mouseEvent->scenePos();
    if(mouseEvent->buttons() & Qt::LeftButton)
    {
        QGraphicsItem * item = itemAt(screenPos, QTransform());
        if(item)
        {
            static_cast<RadioItem *>(item)->updateTopology();
        }
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

#ifdef DEBUG_MESSAGE_SEND
void mGraphicScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    QPointF screenPos = mouseEvent->scenePos();
    if(mouseEvent->button() == Qt::LeftButton)
    {
        QGraphicsItem * item = itemAt(screenPos, QTransform());
        if(item)
        {
            static_cast<RadioItem *>(item)->testSendMessage();
        }
    }
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}
#endif
