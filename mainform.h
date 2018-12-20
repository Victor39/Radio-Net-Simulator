#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <QGraphicsView>
#include "mgraphicscene.h"
#include "radioitem.h"
#include "mtablemodel.h"

namespace Ui {
class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = nullptr);
    ~MainForm();

private slots:
    void on_btnAddDevice_clicked();
    void slotMouseClick(T_RADIO_PARAM params);
    void slotMouseRelease(const RadioId & radioItemId);

private:
    Ui::MainForm * m_ui;
    mGraphicScene * m_scene;
    QList<RadioItem *> m_radios;
    mTableModel * m_radioParams;
};

#endif // MAINFORM_H
