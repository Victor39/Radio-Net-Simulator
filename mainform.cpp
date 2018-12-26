#include "mainform.h"
#include "ui_mainform.h"
#include <QDebug>

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainForm)
{
    m_ui->setupUi(this);
    m_scene = new mGraphicScene(this);
    m_ui->screen->setScene(m_scene);
    m_ui->screen->setCacheMode(QGraphicsView::CacheBackground);
    m_ui->screen->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_ui->screen->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    m_radioParams = new mTableModel(this);
    connect(m_scene, SIGNAL(sigMouseClick(T_RADIO_PARAM)), this, SLOT(slotMouseClick(T_RADIO_PARAM)));
    m_ui->tableParams->setModel(m_radioParams);
    m_ui->tableParams->horizontalHeader()->setStretchLastSection(true);
    m_ui->tableParams->horizontalHeader()->hide();
    m_ui->statusBar->addWidget(&status, 100);
    connect(m_scene, SIGNAL(sigStatus(QString)), this, SLOT(showStatus(QString)));
}

MainForm::~MainForm()
{
    delete m_scene;
    delete m_ui;
}


// -------------------------------------------------- Слоты -----------------------------------------------------

void MainForm::on_btnAddDevice_clicked()
{
    static uint32_t deviceId = 1;
    int32_t x = 150 - 300 * rand() / RAND_MAX;
    int32_t y = 150 - 300 * rand() / RAND_MAX;

    RadioItem * item = new RadioItem(x, y, deviceId++);
    connect(item, SIGNAL(sigStatus(QString)), this, SLOT(showStatus(QString)));
    m_scene->addItem(item);
    m_scene->invalidate();
}

// Слот вызывается при нажатии кнопки мыши на объекте
void MainForm::slotMouseClick(T_RADIO_PARAM params)
{
    m_radioParams->loadModel(params);
    m_ui->tableParams->repaint();
}


// Вывод в строку статуса
void MainForm::showStatus(QString str)
{
    status.setText(str);
}
