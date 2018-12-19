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
//    QGraphicsItem * m_pressedItem {nullptr};

    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent) override;

signals:
    void sigMouseClick(T_RADIO_PARAM params);
    void sigMouseRelease(const RadioId & radioItemId);

public slots:

};

#endif // MGRAPHICSCENE_H
