#include "radioitem.h"
#include <QPainter>
#include <QDebug>
#include <qglobal.h>
#include <simulatorradiopath.h>

RadioItem::RadioItem(int32_t x, int32_t y, RadioId id, QGraphicsObject *parent) :
    QGraphicsObject(parent), m_startPos(x, y),m_curPos(x, y)
{
    m_params.mode() = T_RADIO_MODE::RADIO_MODE_OFF;
    m_params.state() = T_RADIO_STATE::STATE_IDLE;
    m_params.id() = id;
    m_params.callType() = T_CALL::CALL_CIRC;
    m_params.callNumber() = 1;
    QGraphicsObject::setFlag(QGraphicsItem::ItemIsMovable, true);
    QGraphicsObject::setFlag(QGraphicsItem::ItemIsSelectable, true);

    m_radioPath = new SimulatorRadioPath(this);
}


QRectF RadioItem::boundingRect() const
{
    return QRectF(m_startPos.x()-RADIO_SIZE/2, m_startPos.y()-RADIO_SIZE/2, RADIO_SIZE, RADIO_SIZE);
}

void RadioItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(getColorByMode());
    QPen pen = painter->pen();
    if(isSelected())
        pen.setColor(Qt::magenta);
    else
        pen.setColor(Qt::black);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawEllipse(m_startPos.x()-RADIO_SIZE/2, m_startPos.y()-RADIO_SIZE/2, RADIO_SIZE, RADIO_SIZE);

    pen.setColor(Qt::black);
    painter->setPen(pen);
    QString label = QString::number(m_params.id());
    QRectF tpos = getTextRect(label);

    painter->drawText(QRectF(m_startPos.x()-tpos.width()/2, m_startPos.y() + RADIO_SIZE/2 + 5, tpos.width(), tpos.height()), label);

    painter->setBrush(QBrush(Qt::white, Qt::NoBrush));
    painter->setPen(Qt::DotLine);
    painter->setPen(Qt::lightGray);
    painter->drawEllipse(m_startPos.x()-RADIO_DISTANCE/2, m_startPos.y()-RADIO_DISTANCE/2, RADIO_DISTANCE, RADIO_DISTANCE);

    m_curPos.x() = m_startPos.x() + static_cast<int32_t>(this->pos().x());
    m_curPos.y() = m_startPos.y() + static_cast<int32_t>(this->pos().y());

//    qDebug() << m_curPos.x() << " : " << m_curPos.y();
}

 T_RADIO_PARAM RadioItem::getParams() const {

     return m_params;
 }

 const Point2D &RadioItem::getCentrePoint() const
 {
     return m_curPos;
 }

 void RadioItem::testSendMessage()
 {
     uint8_t data[500];
     m_radioPath->radioDataSend(data, 500);
 }

// -------------------------------------------------------------------------------------------------

QBrush RadioItem::getColorByMode()   // Цвет станции в зависимости от режима
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

QRectF RadioItem::getTextRect(QString str)
{
    QFontMetrics metr(QFont("Tahoma"));
    return metr.boundingRect(str);
}
