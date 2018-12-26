#include "radioitem.h"
#include <QPainter>
#include <memory>
#include <QGraphicsView>
#include <QStyle>
#include <QMenu>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QDebug>
#include <qglobal.h>
#include <simulatorradiopath.h>
#include <math.h>
#include "connectionmanager.h"

RadioItem::RadioItem(int32_t x, int32_t y, RadioId id, QGraphicsObject *parent) :
    QGraphicsObject(parent)
{
    m_params.mode() = T_RADIO_MODE::RADIO_MODE_OFF;
    m_params.state() = T_RADIO_STATE::STATE_IDLE;
    m_params.id() = id;
    m_params.callType() = T_CALL::CALL_CIRC;
    m_params.callNumber() = 1;
    QGraphicsObject::setFlag(QGraphicsItem::ItemIsMovable, true);
    QGraphicsObject::setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPos(x, y);

    m_radioPath = new SimulatorRadioPath(this);

    static ConnectionManager & connectionManager = ConnectionManager::instance();
    connectionManager.addRadioItem(this);
}

RadioItem::~RadioItem()
{
    qDebug() << "Removed RadioItem '" << m_params.id() << "'";
}


QRectF RadioItem::boundingRect() const
{
    return QRectF(-RADIO_SIZE/2, -RADIO_SIZE/2, RADIO_SIZE, RADIO_SIZE);
}

void RadioItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


    QPen pen = painter->pen();
    painter->setRenderHint(QPainter::Antialiasing, true);


    // Внутренний круг (станция)
    painter->setBrush(getColorByMode());
    if(isSelected())
        pen.setColor(Qt::magenta);
    else
        pen.setColor(Qt::black);
    pen.setWidth(3);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawEllipse(-RADIO_SIZE/2, -RADIO_SIZE/2, RADIO_SIZE, RADIO_SIZE);

    // Внешний круг (радиус действия)
    painter->setBrush(QBrush(Qt::white, Qt::NoBrush));
    pen.setStyle(Qt::DotLine);
    pen.setColor(Qt::lightGray);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawEllipse(-RADIO_DISTANCE/2, -RADIO_DISTANCE/2, RADIO_DISTANCE, RADIO_DISTANCE);

    // Надпись
    pen.setColor(Qt::black);
    painter->setPen(pen);

    // Связи с соседями
    pen.setColor(Qt::darkBlue);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);

    static ConnectionManager & connectionManager = ConnectionManager::instance();
    std::list<const RadioItem *> neighbors;
    connectionManager.getAvailableNeighborsFor(m_params.id(), neighbors);
    for(auto const & item : neighbors) {
        if(m_params.id() > item->getParams().id()) { // Рисуем только одну линию
            painter->drawLine(mapFromScene(this->getScenePos()), mapFromScene(item->getScenePos()));
        }
    }

    // Формируем строку с подчеркиванием, потому что с пробелом не считает прямоугольник
    //static ConnectionManager & connectionManager = ConnectionManager::instance();
    //connectionManager.findRadioItemBy();
    QString label = QString::number(m_params.id()) + "_[" + QString::number(neighbors.size()) + "]";
    QRectF tpos = getTextRect(label);

    // Повторяем строку, но с пробелом
    label = QString::number(m_params.id()) + " [" + QString::number(neighbors.size()) + "]";
    painter->drawText(QRectF(-tpos.width()/2, RADIO_SIZE/2 + 5, tpos.width(), tpos.height()), label);

    painter->setRenderHint(QPainter::Antialiasing, false);
}

 const T_RADIO_PARAM & RadioItem::getParams() const {

     return m_params;
 }

 T_RADIO_PARAM & RadioItem::getParams() {

     return m_params;
 }

 void RadioItem::updateTopology()
 {
     static ConnectionManager & connectionManager = ConnectionManager::instance();
     connectionManager.updateTopologyFor(m_params.id());
 }

#ifdef DEBUG_MESSAGE_SEND
 void RadioItem::testSendMessage()
 {
     uint8_t data[500];
     m_radioPath->radioDataSend(data, 500);
 }
#endif

// -------------------------------------------------------------------------------------------------

 QBrush RadioItem::getColorByMode() const   // Цвет станции в зависимости от режима
{
    switch(m_params.mode())
    {
        case T_RADIO_MODE::RADIO_MODE_OFF:
            return QBrush(Qt::gray);
        case T_RADIO_MODE::RADIO_MODE_TX:
            return QBrush(Qt::red);
        case T_RADIO_MODE::RADIO_MODE_RX:
            return QBrush(Qt::yellow);
    }
    return QBrush(Qt::white, Qt::NoBrush);
}

/**
 * @brief RadioItem::getTextRect - функция возвращает прямоугольник вокруг заданного текста
 * @param str - исходный текст
 * @return - прямоугольник
 */
 QRectF RadioItem::getTextRect(const QString & str) const
{
    QFontMetrics metr(QFont("Tahoma"));
    return metr.boundingRect(str);
}

/**
 * @brief RadioItem::getScenePos - функция возвращает координаты объекта на сцене
 * @return
 */
QPointF RadioItem::getScenePos() const
{
    return scenePos();
}

/**
 * @brief RadioItem::distance - функция возвращает расстояние между двумя точками на плоскости
 * @param x1, y1 - координаты первой точки
 * @param x2, y2 - координаты второй точки
 * @return - расстояние
 */
uint32_t RadioItem::distance(qreal x1, qreal y1, qreal x2, qreal y2) const
{
    uint32_t dist = static_cast<uint32_t>(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
    return dist;
}

/**
 * @brief RadioItem::distanceTo - функция возвращает расстояние от текущего объекта до объекта item на сцене
 * @param item - целевой объект
 * @return - расстояние
 */
uint32_t RadioItem::distanceTo(const RadioItem *item) const
{
    return distance(this->scenePos().x(), this->scenePos().y(), item->getScenePos().x(), item->getScenePos().y());
}

/**
 * @brief RadioItem::contextMenuEvent - контекстное меню объекта
 * @param event
 */
void RadioItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if (!isSelected() && scene())
    {
        scene()->clearSelection();
        setSelected(true);
    }

    QMenu menu;
    QAction *switchAction;
    QAction *delAction = menu.addAction("Удалить");
    if(m_params.mode() != T_RADIO_MODE::RADIO_MODE_OFF)
        switchAction = menu.addAction("Выключить");
    else
        switchAction = menu.addAction("Включить");

    QAction *selectedAction = menu.exec(event->screenPos());

    if (selectedAction == delAction)
        deleteSelectedItems(scene());
    else if (selectedAction == switchAction)
    {
        m_params.mode() = (m_params.mode() == T_RADIO_MODE::RADIO_MODE_OFF) ? T_RADIO_MODE::RADIO_MODE_RX:T_RADIO_MODE::RADIO_MODE_OFF;
        scene()->invalidate();
    }
}

/**
 * @brief RadioItem::deleteSelectedItems - функция удаляет объект со сцены
 * @param scene
 */
void RadioItem::deleteSelectedItems(QGraphicsScene *scene)
{
    if (!scene)
        return;

    QList<QGraphicsItem *> selected;
    selected = scene->selectedItems();

    foreach (QGraphicsItem *item, selected) {
        RadioItem *itemBase = qgraphicsitem_cast<RadioItem *>(item);
        if (itemBase) {
            static ConnectionManager & connectionManager = ConnectionManager::instance();
            connectionManager.removeRadioItemBy(itemBase->getParams().id());
            delete itemBase;
        }
    }
}
