#ifndef RADIOITEM_H
#define RADIOITEM_H

#include <stdint.h>
#include <QGraphicsItem>

using RadioId = uint32_t;

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

class RadioItem;

class T_RADIO_PARAM {

public:
    T_RADIO_PARAM() = default;
    ~T_RADIO_PARAM() = default;

    const T_RADIO_MODE & mode() const { return m_mode; }
    T_RADIO_MODE & mode() { return m_mode; }
    const T_RADIO_STATE & state() const { return m_state; }
    T_RADIO_STATE & state() { return m_state; }
    const RadioId & id() const { return m_id; }
    RadioId & id() { return m_id; }
    const T_CALL & callType() const { return m_callType; }
    T_CALL & callType() { return m_callType; }
    const uint32_t & callNumber() const { return m_callNumber; }
    uint32_t & callNumber() { return m_callNumber; }
    const uint32_t & txFreqIndex() const { return m_txFreqIndex; }
    uint32_t & txFreqIndex() { return m_txFreqIndex; }
    const uint32_t & rxFreqIndex() const { return m_rxFreqIndex; }
    uint32_t & rxFreqIndex() { return m_rxFreqIndex; }
    const uint32_t & dataTransmissionRate() const { return m_dataTransmissionRate; }
    uint32_t & dataTransmissionRate() { return m_dataTransmissionRate; }

private:
    T_RADIO_MODE m_mode                 {T_RADIO_MODE::RADIO_MODE_OFF};
    T_RADIO_STATE m_state               {T_RADIO_STATE::STATE_IDLE};
    RadioId m_id                        {0};
    T_CALL m_callType                   {T_CALL::CALL_ID};
    uint32_t m_callNumber               {0};
    uint32_t m_txFreqIndex              {0};
    uint32_t m_rxFreqIndex              {0};
    uint32_t m_dataTransmissionRate     {100};
};


class SimulatorRadioPath;

class RadioItem : public QGraphicsObject
{
    Q_OBJECT
public:
    static constexpr auto RADIO_DISTANCE     {350};
    static constexpr auto RADIO_SIZE         {25};

    explicit RadioItem(int32_t x, int32_t y, RadioId id, QGraphicsObject *parent = nullptr);
    virtual ~RadioItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    const T_RADIO_PARAM & getParams() const;
    T_RADIO_PARAM & getParams();

    void updateTopology();

    QPointF getScenePos() const;
    uint32_t distanceTo(const RadioItem *item) const;

#ifdef DEBUG_MESSAGE_SEND
    void testSendMessage();
#endif

private:
    T_RADIO_PARAM m_params;     // Таблица настроек
    QBrush getColorByMode() const;    // Цвет станции в зависимости от режима
    QRectF getTextRect(const QString & str) const;

    SimulatorRadioPath * m_radioPath;

    uint32_t distance(qreal x1, qreal y1, qreal x2, qreal y2) const;

    void deleteSelectedItems(QGraphicsScene *scene);
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

signals:
    void sigStatus(QString str);

public slots:

};

#endif // RADIOITEM_H
