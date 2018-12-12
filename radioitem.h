#ifndef RADIOITEM_H
#define RADIOITEM_H

#include <stdint.h>
#include <QGraphicsItem>
#include <point2d.h>




enum class T_RADIO_MODE {
    RADIO_MODE_OFF,
    RADIO_MODE_RX,
    RADIO_MODE_TX,
};

enum class T_RADIO_STATE {
    STATE_IDLE,
    STATE_SYNC,
    STATE_CALL,
 };

enum class T_CALL {
    CALL_ID,
    CALL_GROUP,
    CALL_CIRC,
};

class T_RADIO_PARAM {

public:
    T_RADIO_PARAM()
    {
        m_mode = T_RADIO_MODE::RADIO_MODE_OFF;
        m_state = T_RADIO_STATE::STATE_IDLE;
        m_id = 0;
        m_callType = T_CALL::CALL_ID;
        m_callNumber = 0;
    }

    const T_RADIO_MODE & mode() const { return m_mode; }
    T_RADIO_MODE & mode() { return m_mode; }
    const T_RADIO_STATE & state() const { return m_state; }
    T_RADIO_STATE & state() { return m_state; }
    const uint32_t & id() const { return m_id; }
    uint32_t & id() { return m_id; }
    const T_CALL & callType() const { return m_callType; }
    T_CALL & callType() { return m_callType; }
    const uint32_t & callNumber() const { return m_callNumber; }
    uint32_t & callNumber() { return m_callNumber; }

private:
    T_RADIO_MODE m_mode;          // текущий режим
    T_RADIO_STATE m_state;        // текущее состояние
    uint32_t m_id;                // номер станции
    T_CALL m_callType;            // тип текущего вызова
    uint32_t m_callNumber;        // номер текущего вызова
};


class RadioItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit RadioItem(int32_t x, int32_t y, uint32_t id, QGraphicsObject *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    T_RADIO_PARAM getParams() const;

    const Point2D & getCentrePoint() const;

private:

    static constexpr auto RADIO_DISTANCE     {200};
    static constexpr auto RADIO_SIZE         {15};

    Point2D m_startPos;         // Координаты центра при создании (необходимо помнить для отрисовки)
    Point2D m_curPos;           // Текущие координаты центра
    T_RADIO_PARAM m_params;     // Таблица настроек
    QBrush getColorByMode();    // Цвет станции в зависимости от режима
    QRectF getTextRect(QString str);

signals:

public slots:

};

#endif // RADIOITEM_H
