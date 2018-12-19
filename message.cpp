#include "message.h"

Message::Message(const uint8_t * pData, const size_t length, const uint32_t byteRate, const uint32_t freqIndex, const uint32_t sourceId) {
    m_startSendTime = QTime::currentTime();
    m_durationTimeMs = (1000UL * length) / byteRate;
    m_freqIndex = freqIndex;
    std::copy(&pData[0], &pData[length], back_inserter(m_data));
    m_sourceId = sourceId;

    m_timer = new QTimer();
//    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
}

Message::~Message()
{
    if(m_timer != nullptr) {
        m_timer->stop();
        delete m_timer;
    }
}

const QTime &Message::startSendTime() const
{
    return m_startSendTime;
}

const uint32_t &Message::durationTimeMs() const
{
    return m_durationTimeMs;
}

const uint32_t &Message::freqIndex() const
{
    return m_freqIndex;
}

const uint8_t * Message::data() const
{
    return m_data.data();
}

size_t Message::length() const
{
    return m_data.size();
}

const uint32_t &Message::sourceId() const
{
    return m_sourceId;
}

QTimer *Message::timer()
{
    return m_timer;
}

