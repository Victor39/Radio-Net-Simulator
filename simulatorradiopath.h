#ifndef SIMULATORRADIOPATH_H
#define SIMULATORRADIOPATH_H

#include "halinterfaces/include/radiopath.h"
#include "message.h"
#include <QDebug>
#include <QSharedPointer>


class RadioItem;

class SimulatorRadioPath : public QObject, public hal::RadioPath
{
    Q_OBJECT
public:
    SimulatorRadioPath(RadioItem * pOwner);
    virtual ~SimulatorRadioPath() override;

    virtual void initRadioPath () override;
    virtual void radioDataSend (const uint8_t * pData, const size_t length) override;
    virtual void radioDataReceive (const uint8_t * pData, const size_t length) override;
    virtual void radioTxOn () override;
    virtual void radioTxOff () override;
    virtual void radioRxOn () override;
    virtual void radioRxOff () override;
    virtual void radioSetTxFreqBy (const uint32_t freqIndex) override;
    virtual void radioSetRxFreqBy (const uint32_t freqIndex) override;
    virtual void radioFreqListCalibration (const uint32_t * pFreqIndexList, const size_t size) override;

private:
    RadioItem * m_pOwner;

signals:
    void sigSendMessage(QSharedPointer<Message> msg);

};

#endif // SIMULATORRADIOPATH_H
