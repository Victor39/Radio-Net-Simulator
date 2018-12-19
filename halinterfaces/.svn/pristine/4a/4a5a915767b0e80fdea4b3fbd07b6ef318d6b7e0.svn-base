/*!
    \brief      Интерфейсы уровня аппаратной абстракции (Hardware Abstraction Layer) для абстрактной платформы радиостанции
    \author     kharitonov-ev
    \version    1.0
    \date       30.11.2017
*/

#pragma once

// !! это концепт подключения заголовочников, определяющий некоторые объекты, которые могут использоваться в интерфейсах HAL
// возможно, уровень HAL будет перепсан в класс, но ещё не весь код написан на c++
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
 *  \details    Инициализация уровня HAL: управление радиотрактом, внешними интерфейсами передачи данных на внешние устройства, внешней аппратурой и т.д.
 *  \return     NONE
 */
void HAL_init();

// ----------------------------------------------------- РАБОТА С УСИЛИТЕЛЕМ МОЩНОСТИ ------------------------------------------------------

/**
 *  \details    Включение усилителя мощности сигнала. [Необходимо согласовать с работой передатчика/приёмника/АНСУ/БАФ и тд...]
 *  [Тут желательно описать что при этом происходит]
 *  \param[in, out]  NONE
 *  \return          NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_amplifierOn();


/**
 *  \details    Выключение усилителя мощности сигнала. [Необходимо согласовать с работой передатчика/приёмника/АНСУ/БАФ и тд...]
 *  [Тут желательно описать что при этом происходит]
 *  \param[in, out]  NONE
 *  \return          NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_amplifierOff();


// ------------------------------------------------ РАБОТА С АНТЕННО-СОГЛАСУЮЩИМ УСТРОЙСТВОМ (АнСУ) -----------------------------
// понятия, не имею, что с ним можно сделать, поэтому пишу наугад, надеюсь на помощь коллег =)

/**
 *  \details    Включение АНСУ. [Необходимо согласовать с работой передатчика/приёмника/АНСУ/БАФ и тд...]
 *  [Тут желательно описать что при этом происходит]
 *  \param[in, out]  NONE
 *  \return          NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_antennaTunerOn();


/**
 *  \details    Выключение АНСУ. [Необходимо согласовать с работой передатчика/приёмника/АНСУ/БАФ и тд...]
 *  [Тут желательно описать что при этом происходит]
 *  \param[in, out]  NONE
 *  \return          NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_antennaTunerOff();

// ------------------------------------------------ РАБОТА С БЛОКОМ АНТЕННЫХ ФИЛЬТРОВ (БАФ) -----------------------------
// та же история что и с АнСУ...

/**
 *  \details    Включение БАФа. [Необходимо согласовать с работой передатчика/приёмника/АНСУ/БАФ и тд...]
 *  [Тут желательно описать что при этом происходит]
 *  \param[in, out]  NONE
 *  \return          NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_antennaFilterBlockOn();


/**
 *  \details    Выключение БАФа. [Необходимо согласовать с работой передатчика/приёмника/АНСУ/БАФ и тд...]
 *  [Тут желательно описать что при этом происходит]
 *  \param[in, out]  NONE
 *  \return          NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_antennaFilterBlockOff();


// ------------------------------------------------ РАБОТА С ВНЕШНИМИ ИНТЕРФЕЙСАМИ ПЕРЕДАЧИ ДАННЫХ: USB, RS-232 И ТД -----------------------------
/**
 *  \details    Передача данных по USB.
 *  \param[in]  usbdata_t pUsbData  - указатель на массив передаваемых данных
 *  \param[in]  usbDataLen_t length - длина передаваемых данных в байтах
 *  \return     NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_usbDataSend(usbdata_t pUsbData, usbDataLen_t length);


/**
 *  \details    Обработчик события приёма данных по USB.
 *  \param[out] usbdata_t pUsbData  - указатель на массив, куда будут записаны принятые данные
 *  \param[in]  usbDataLen_t length - длина передаваемых данных в байтах
 *  \return     NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_usbDataReceive(usbdata_t pUsbData, usbDataLen_t length);

/**
 *  \details    Передача данных по RS-232.
 *  \param[in]  rs232data_t pRs232Data  - указатель на массив передаваемых данных
 *  \param[in]  usbDataLen_t length - длина передаваемых данных в байтах
 *  \return     NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_rs232DataSend(rs232data_t pRs232Data, rs232DataLen_t length);

/**
 *  \details    Обработчик события приёма данных по RS-232.
 *  \param[out] rs232data_t pRs232Data  - указатель на массив, куда будут записаны принятые данные
 *  \param[in]  usbDataLen_t length - длина передаваемых данных в байтах
 *  \return     NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_rs232DataReceive(rs232data_t pRs232Data, rs232DataLen_t length);

/**
 *  \details    Передача данных по Bluetooth.
 *  \param[in]  bluetoothData_t pBluetoothData  - указатель на массив передаваемых данных
 *  \param[in]  bluetoothDataLen_t length - длина передаваемых данных в байтах
 *  \return     NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_bluetoothDataSend(bluetoothData_t pBluetoothData, bluetoothDataLen_t length);

/**
 *  \details    Обработчик события приёма данных по Bluetooth.
 *  \param[out] bluetoothData_t pBluetoothData  - указатель на массив, куда будут записаны принятые данные
 *  \param[in]  bluetoothusbDataLen_t length - длина передаваемых данных в байтах
 *  \return     NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_bluetoothDataReceive(bluetoothData_t pBluetoothData, bluetoothDataLen_t length);

// ------------------------------------------------ РАБОТА С ПРОФИЛЕМ/КАНАЛОМ СТАНЦИИ -----------------------------
/**
 *  \details    Обработчик события переключения канала/профиля радиостанции. Все действия, производимые при переключении канала описываются здесь.
 *  \param[in]  chanProf_t pChanProfile  - номер профиля/канала в радиостанции
 *  \return     NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_switchChanProfile(chanProf_t pChanProfile);

// --------------------------------------------------- РАБОТА С ВНЕШНЕЙ ПЕРИФЕРИЕЙ ---------------------------------------------

/**
 *  \details    Отправка сообщения от back-end аппаратуры внешней периферии.
 *  \param[in]  sysEventGuid_t eventGuid - глобальный идентификатор события в системе
 *  \return     NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_sendToExtPeiphery(sysEventGuid_t eventGuid);


/**
 *  \details    Перегруженная фукнция. Отправка сообщения от back-end аппаратуры внешней периферии.
 *  \param[in]  sysEventGuid_t eventGuid - глобальный идентификатор события в системе
 *  \param[in]  extPeriphData_t pData - указатель на массив с передаваемыми данными
 *  \param[in]  extPeriphDataLen_t length - длина передаваемого сообщения, не включая eventGuid
 *  \return     NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_sendToExtPeiphery(sysEventGuid_t eventGuid, extPeriphData_t pData, extPeriphDataLen_t length);


/**
 *  \details    Приём сообщения back-end аппратурой от внешней периферии .
 *  \param[in]  sysEventGuid_t eventGuid - глобальный идентификатор события в системе
 *  \param[out]  extPeriphData_t pData - указатель на массив, куда будут записаны принятые данные
 *  \param[in]  extPeriphDataLen_t length - длина передаваемого сообщения, не включая eventGuid
 *  \return     sysEventGuid_t - глобальный идентификатор сообщения
 *  [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
sysEventGuid_t HAL_receiveFromExtPeiphery(extPeriphData_t pData, extPeriphDataLen_t length);

/**
 *  \details    Отправка сообщения внешней периферией на back-end аппаратуру.
 *  \param[in]  sysEventGuid_t eventGuid - глобальный идентификатор события в системе
 *  \return     NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_sendToBackEnd(sysEventGuid_t eventGuid);


/**
 *  \details    Перегруженная фукнция. Отправка сообщения внешней периферией на back-end аппаратуру.
 *  \param[in]  sysEventGuid_t eventGuid - глобальный идентификатор события в системе
 *  \param[in]  backEndData_t pData - указатель на массив с передаваемыми данными
 *  \param[in]  extPeriphDataLen_t length - длина передаваемого сообщения, не включая eventGuid
 *  \return     NONE [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
void HAL_sendToBackEnd(sysEventGuid_t eventGuid, backEndData_t pData, backEndDataLen_t length);

/**
 *  \details    Приём сообщения от внешней периферией от back-end аппаратуры.
 *  \param[in]  sysEventGuid_t eventGuid - глобальный идентификатор события в системе
 *  \param[out]  extPeriphData_t pData - указатель на массив, куда будут записаны принятые данные
 *  \param[in]  extPeriphDataLen_t length - длина передаваемого сообщения, не включая eventGuid
 *  \return     sysEventGuid_t - глобальный идентификатор сообщения
 *  [возможно, надо выводить результат работы: успех/неудача: тип ошибки и тд...]
 */
sysEventGuid_t HAL_receiveFromBackEnd(backEndData_t pData, backEndDataLen_t length);
