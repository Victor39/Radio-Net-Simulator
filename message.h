#ifndef MESSAGE_H
#define MESSAGE_H

#include <QTime>
#include <vector>

class Message
{
public:
    Message () = delete;
    Message(const Message & obj) = delete;
    Message(const uint8_t * pData, const size_t length, const uint32_t byteRate, const uint32_t freqIndex, const uint32_t sourceId);
    ~Message();

    const QTime & startSendTime() const;
    const uint32_t & durationTimeMs () const;
    const uint32_t & freqIndex () const;
    const uint8_t * data() const;
    size_t length() const;
    const uint32_t & sourceId() const;

private:
    QTime m_startSendTime;
    uint32_t m_durationTimeMs;
    uint32_t m_freqIndex;
    std::vector<uint8_t> m_data;
    uint32_t m_sourceId;

};

#endif // MESSAGE_H
