#include <QComboBox>
#include "mtablemodel.h"

/**
 * @brief mTableModel::mTableModel - конструктор
 * @param parent
 */
mTableModel::mTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

// --------------------------------- Обязательные реализации ---------------------------------
/**
 * @brief mTableModel::rowCount - функция возвращает число строк таблицы
 * @param parent
 * @return - число строк
 */
int mTableModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);

    if(m_radioParam.id() == 0)
        return 0;
    return m_numberOfRow;
}

/**
 * @brief mTableModel::columnCount - функция возвращает число столбцов таблицы
 * @param parent
 * @return - число столбцов
 */
int mTableModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);

    if(m_radioParam.id() == 0)
        return 0;
    return 1;
}

/**
 * @brief mTableModel::data - функция возвращает данные в ячейках таблицы
 * @param index - координаты ячейки
 * @param role - роль в отображении
 * @return - значение, показываемое в ячейке
 */
QVariant mTableModel::data(const QModelIndex & index, int role) const
{
    int row = index.row(); // номер строки
    //int col = index.column();


    if(m_radioParam.id() != 0)
    {
        if(role == Qt::DisplayRole)
        {
            if(row < m_numberOfRow)
            {
                switch(row)
                {
                    case 0: // id
                        return QVariant(m_radioParam.id());
                    case 1: // mode
                        return QVariant(getNameOfRadioMode(m_radioParam.mode()));
                    case 2: // state
                        return QVariant(getNameOfRadioState(m_radioParam.state()));
                    case 3: // callType
                        return QVariant(getNameOfCallType(m_radioParam.callType()));
                    case 4: // callNumber
                        if(m_radioParam.callType() != T_CALL::CALL_CIRC)
                            return QVariant(m_radioParam.callNumber());
                        else
                            return QVariant("-");
                }
            }
        }
    }
    return QVariant();
}

/**
 * @brief mTableModel::headerData - функция выдает заголовки таблицы
 * @param section - номер заголовка
 * @param orientation - ориентация (верт/гориз)
 * @param role - роль в отображении
 * @return - текст, который будет показан
 */
QVariant mTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QStringList headerNames = QStringList() << "ID" << "Режим" << "Статус" << "Тип вызова" << "Номер вызова";

    if((role == Qt::DisplayRole) && (orientation == Qt::Vertical))
    {
        if(section < headerNames.length())
            return QVariant(headerNames[section]);
    }
    return QVariant();
}

// -------------------------------------------------------------------------------------------

/**
 * @brief mTableModel::getNameOfRadioMode - функция возвращает текстовое описание режима радиостанции
 * @param mode - режим радиостанции
 * @return - строка
 */
QString mTableModel::getNameOfRadioMode(const T_RADIO_MODE & mode) const
{
    QStringList nameOfRadioMode = QStringList() << "Выкл." << "Прием" <<"Передача";
    return nameOfRadioMode[static_cast<int>(mode)];
}

/**
 * @brief mTableModel::getNameOfRadioState - функция возвращает текстовое описание состояния радиостанции
 * @param state - состояние радиостанции
 * @return - строка
 */
QString mTableModel::getNameOfRadioState(const T_RADIO_STATE & state) const
{
    QStringList nameOfRadioState = QStringList() << "Ожидание" << "Синхронизация" <<"Вызов";
    return nameOfRadioState[static_cast<int>(state)];
}

/**
 * @brief mTableModel::getNameOfCallType - функция возвращает текстовое описание типа вызова.
 *      ВНИМАНИЕ! Текст должен соответствовать структуре T_RADIO_STATE!!!
 * @param calltype - тип вызова
 * @return - строка
 */
QString mTableModel::getNameOfCallType(const T_CALL & calltype) const
{
    QStringList nameOfCallType = QStringList() << "Адрес" << "Группа" << "Все";
    return nameOfCallType[static_cast<int>(calltype)];
}

/**
 * @brief mTableModel::loadModel - функция загружает данные в модель
 * @param params - структура параметров
 */
void mTableModel::loadModel(T_RADIO_PARAM params)
{
    beginResetModel();
    m_radioParam = params;
    endResetModel();
}
