#include "simulatorradiopath.h"
#include <qglobal.h>
#include "message.h"
#include "radioitem.h"
#include "connectionmanager.h"
#include <QSharedPointer>

SimulatorRadioPath::SimulatorRadioPath(RadioItem * pOwner) : m_pOwner(pOwner)
{
    ConnectionManager & connectionManager = ConnectionManager::instance();
    QObject::connect(this, SIGNAL(sigSendMessage(QSharedPointer<Message> msg)), &connectionManager, SLOT(slotSendMessage(QSharedPointer<Message> msg)));
}

SimulatorRadioPath::~SimulatorRadioPath()
{

}

void SimulatorRadioPath::initRadioPath()
{

}

void SimulatorRadioPath::radioDataSend(const uint8_t *pData, const size_t length)
{
    QSharedPointer<Message> msg (new Message(pData, length,
                                    m_pOwner->getParams().dataTransmissionRate(), m_pOwner->getParams().txFreqIndex(), m_pOwner->getParams().id()));
    emit sigSendMessage(msg);

}

void SimulatorRadioPath::radioDataReceive(const uint8_t *pData, const size_t length)
{
    Q_UNUSED(pData);
    Q_UNUSED(length);
}

void SimulatorRadioPath::radioTxOn()
{

}

void SimulatorRadioPath::radioTxOff()
{

}

void SimulatorRadioPath::radioRxOn()
{

}

void SimulatorRadioPath::radioRxOff()
{

}

void SimulatorRadioPath::radioSetTxFreqBy(const uint32_t freqIndex)
{
    Q_UNUSED(freqIndex);
}

void SimulatorRadioPath::radioSetRxFreqBy(const uint32_t freqIndex)
{
    Q_UNUSED(freqIndex);
}

void SimulatorRadioPath::radioFreqListCalibration(const uint32_t *pFreqIndexList, const size_t size)
{
    Q_UNUSED(pFreqIndexList);
    Q_UNUSED(size);
}
