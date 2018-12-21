#ifndef MGRAPHICSCENE_H
#define MGRAPHICSCENE_H

#include <QGraphicsScene>
#include "radioitem.h"

typedef struct T_RADIO_NB
{
    uint32_t id;    // id станции
    int32_t x;      // х-координата станции
    int32_t y;      // Y-координата станции
    QList<uint32_t> nb;  // Список соседей
    //    uint32_t getDistance(T_RADIO_NB neigh)
    //    {
    //        uint32_t dist = sqrt((x - neigh.x)*(x - neigh.x) + (y - neigh.y)*(y - neigh.y));
    //        return dist;
    //    }
    //    bool operator==(const T_RADIO_NB &other)
    //    {
    //        if((id == other.id) && (nb == other.nb))
    //            return true;
    //        return false;
    //    }
} T_RADIO_NB;

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
    QList<T_RADIO_NB> listNbStore;

signals:
    void sigMouseClick(T_RADIO_PARAM params);
    void sigMouseRelease(RadioItem * radiItem);
    void nbChanged(QList<T_RADIO_NB> listNbStore);
    void sigStatus(QString str);

public slots:
    void slotChanged(const QList<QRectF> & region);
};

#endif // MGRAPHICSCENE_H
