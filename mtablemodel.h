#ifndef MTABLEMODEL_H
#define MTABLEMODEL_H

#include <QAbstractTableModel>
#include "radioitem.h"

class mTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit mTableModel(QObject *parent = nullptr);
    void loadModel(T_RADIO_PARAM params);

private:
    T_RADIO_PARAM m_radioParam;
    const int m_numberOfRow {5};
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    int columnCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QString getNameOfRadioMode(const T_RADIO_MODE & mode) const;
    QString getNameOfRadioState(const T_RADIO_STATE & state) const;
    QString getNameOfCallType(const T_CALL & calltype) const;

signals:

public slots:

};

#endif // MTABLEMODEL_H
