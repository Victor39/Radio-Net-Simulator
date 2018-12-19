/*!
    \brief      ���������� ������ ���������� ���������� (Hardware Abstraction Layer) ��� ����������� ��������� ������������
    \author     kharitonov-ev
    \version    1.0
    \date       30.11.2017
*/

#pragma once

// !! ��� ������� ����������� ��������������, ������������ ��������� �������, ������� ����� �������������� � ����������� HAL
// ��������, ������� HAL ����� �������� � �����, �� ��� �� ���� ��� ������� �� c++
#ifdef PLATFORM_MOPCH
#include "haldsp6713/haldsp6713.h"
#endif

#ifdef PLATFORM_BEKAS_DSP5509
#include "halbekas/halbekas5509.h"
#endif

#ifdef PLATFORM_BEKAS_DSP6748
#include "halbekas/halbekas6748.h"
#endif

/**
 *  \details    ������������� ������ HAL: ���������� ������������, �������� ������������ �������� ������ �� ������� ����������, ������� ���������� � �.�.
 *  \return     NONE
 */
void HAL_init();

// ----------------------------------------------------- ������ � ���������� �������� ------------------------------------------------------

/**
 *  \details    ��������� ��������� �������� �������. [���������� ����������� � ������� �����������/��������/����/��� � ��...]
 *  [��� ���������� ������� ��� ��� ���� ����������]
 *  \param[in, out]  NONE
 *  \return          NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_amplifierOn();


/**
 *  \details    ���������� ��������� �������� �������. [���������� ����������� � ������� �����������/��������/����/��� � ��...]
 *  [��� ���������� ������� ��� ��� ���� ����������]
 *  \param[in, out]  NONE
 *  \return          NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_amplifierOff();


// ------------------------------------------------ ������ � �������-����������� ����������� (����) -----------------------------
// �������, �� ����, ��� � ��� ����� �������, ������� ���� ������, ������� �� ������ ������ =)

/**
 *  \details    ��������� ����. [���������� ����������� � ������� �����������/��������/����/��� � ��...]
 *  [��� ���������� ������� ��� ��� ���� ����������]
 *  \param[in, out]  NONE
 *  \return          NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_antennaTunerOn();


/**
 *  \details    ���������� ����. [���������� ����������� � ������� �����������/��������/����/��� � ��...]
 *  [��� ���������� ������� ��� ��� ���� ����������]
 *  \param[in, out]  NONE
 *  \return          NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_antennaTunerOff();

// ------------------------------------------------ ������ � ������ �������� �������� (���) -----------------------------
// �� �� ������� ��� � � ����...

/**
 *  \details    ��������� ����. [���������� ����������� � ������� �����������/��������/����/��� � ��...]
 *  [��� ���������� ������� ��� ��� ���� ����������]
 *  \param[in, out]  NONE
 *  \return          NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_antennaFilterBlockOn();


/**
 *  \details    ���������� ����. [���������� ����������� � ������� �����������/��������/����/��� � ��...]
 *  [��� ���������� ������� ��� ��� ���� ����������]
 *  \param[in, out]  NONE
 *  \return          NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_antennaFilterBlockOff();


// ------------------------------------------------ ������ � �������� ������������ �������� ������: USB, RS-232 � �� -----------------------------
/**
 *  \details    �������� ������ �� USB.
 *  \param[in]  usbdata_t pUsbData  - ��������� �� ������ ������������ ������
 *  \param[in]  usbDataLen_t length - ����� ������������ ������ � ������
 *  \return     NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_usbDataSend(usbdata_t pUsbData, usbDataLen_t length);


/**
 *  \details    ���������� ������� ����� ������ �� USB.
 *  \param[out] usbdata_t pUsbData  - ��������� �� ������, ���� ����� �������� �������� ������
 *  \param[in]  usbDataLen_t length - ����� ������������ ������ � ������
 *  \return     NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_usbDataReceive(usbdata_t pUsbData, usbDataLen_t length);

/**
 *  \details    �������� ������ �� RS-232.
 *  \param[in]  rs232data_t pRs232Data  - ��������� �� ������ ������������ ������
 *  \param[in]  usbDataLen_t length - ����� ������������ ������ � ������
 *  \return     NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_rs232DataSend(rs232data_t pRs232Data, rs232DataLen_t length);

/**
 *  \details    ���������� ������� ����� ������ �� RS-232.
 *  \param[out] rs232data_t pRs232Data  - ��������� �� ������, ���� ����� �������� �������� ������
 *  \param[in]  usbDataLen_t length - ����� ������������ ������ � ������
 *  \return     NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_rs232DataReceive(rs232data_t pRs232Data, rs232DataLen_t length);

/**
 *  \details    �������� ������ �� Bluetooth.
 *  \param[in]  bluetoothData_t pBluetoothData  - ��������� �� ������ ������������ ������
 *  \param[in]  bluetoothDataLen_t length - ����� ������������ ������ � ������
 *  \return     NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_bluetoothDataSend(bluetoothData_t pBluetoothData, bluetoothDataLen_t length);

/**
 *  \details    ���������� ������� ����� ������ �� Bluetooth.
 *  \param[out] bluetoothData_t pBluetoothData  - ��������� �� ������, ���� ����� �������� �������� ������
 *  \param[in]  bluetoothusbDataLen_t length - ����� ������������ ������ � ������
 *  \return     NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_bluetoothDataReceive(bluetoothData_t pBluetoothData, bluetoothDataLen_t length);

// ------------------------------------------------ ������ � ��������/������� ������� -----------------------------
/**
 *  \details    ���������� ������� ������������ ������/������� ������������. ��� ��������, ������������ ��� ������������ ������ ����������� �����.
 *  \param[in]  chanProf_t pChanProfile  - ����� �������/������ � ������������
 *  \return     NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_switchChanProfile(chanProf_t pChanProfile);

// --------------------------------------------------- ������ � ������� ���������� ---------------------------------------------

/**
 *  \details    �������� ��������� �� back-end ���������� ������� ���������.
 *  \param[in]  sysEventGuid_t eventGuid - ���������� ������������� ������� � �������
 *  \return     NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_sendToExtPeiphery(sysEventGuid_t eventGuid);


/**
 *  \details    ������������� �������. �������� ��������� �� back-end ���������� ������� ���������.
 *  \param[in]  sysEventGuid_t eventGuid - ���������� ������������� ������� � �������
 *  \param[in]  extPeriphData_t pData - ��������� �� ������ � ������������� �������
 *  \param[in]  extPeriphDataLen_t length - ����� ������������� ���������, �� ������� eventGuid
 *  \return     NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_sendToExtPeiphery(sysEventGuid_t eventGuid, extPeriphData_t pData, extPeriphDataLen_t length);


/**
 *  \details    ���� ��������� back-end ���������� �� ������� ��������� .
 *  \param[in]  sysEventGuid_t eventGuid - ���������� ������������� ������� � �������
 *  \param[out]  extPeriphData_t pData - ��������� �� ������, ���� ����� �������� �������� ������
 *  \param[in]  extPeriphDataLen_t length - ����� ������������� ���������, �� ������� eventGuid
 *  \return     sysEventGuid_t - ���������� ������������� ���������
 *  [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
sysEventGuid_t HAL_receiveFromExtPeiphery(extPeriphData_t pData, extPeriphDataLen_t length);

/**
 *  \details    �������� ��������� ������� ���������� �� back-end ����������.
 *  \param[in]  sysEventGuid_t eventGuid - ���������� ������������� ������� � �������
 *  \return     NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_sendToBackEnd(sysEventGuid_t eventGuid);


/**
 *  \details    ������������� �������. �������� ��������� ������� ���������� �� back-end ����������.
 *  \param[in]  sysEventGuid_t eventGuid - ���������� ������������� ������� � �������
 *  \param[in]  backEndData_t pData - ��������� �� ������ � ������������� �������
 *  \param[in]  extPeriphDataLen_t length - ����� ������������� ���������, �� ������� eventGuid
 *  \return     NONE [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
void HAL_sendToBackEnd(sysEventGuid_t eventGuid, backEndData_t pData, backEndDataLen_t length);

/**
 *  \details    ���� ��������� �� ������� ���������� �� back-end ����������.
 *  \param[in]  sysEventGuid_t eventGuid - ���������� ������������� ������� � �������
 *  \param[out]  extPeriphData_t pData - ��������� �� ������, ���� ����� �������� �������� ������
 *  \param[in]  extPeriphDataLen_t length - ����� ������������� ���������, �� ������� eventGuid
 *  \return     sysEventGuid_t - ���������� ������������� ���������
 *  [��������, ���� �������� ��������� ������: �����/�������: ��� ������ � ��...]
 */
sysEventGuid_t HAL_receiveFromBackEnd(backEndData_t pData, backEndDataLen_t length);
