#include <memory>
#include "mainform.h"
#include "ui_mainform.h"
#include "connectionmanager.h"
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
    connect(m_scene, SIGNAL(sigMouseRelease(const RadioId &)), this, SLOT(slotMouseRelease(const RadioId &)));
    m_ui->tableParams->setModel(m_radioParams);
    m_ui->tableParams->horizontalHeader()->setStretchLastSection(true);
    m_ui->tableParams->horizontalHeader()->hide();
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
    int32_t x = 300 * rand() / RAND_MAX;
    int32_t y = 300 * rand() / RAND_MAX;

    std::shared_ptr<RadioItem> item = std::shared_ptr<RadioItem>(new RadioItem(75 + x, 75 + y, deviceId++));
    static ConnectionManager & connectionManager = ConnectionManager::instance();
    connectionManager.addRadioItem(item);

    m_scene->addItem(item.get());
    m_scene->invalidate();
}

// Слот вызывается при нажатии кнопки мыши на объекте
void MainForm::slotMouseClick(T_RADIO_PARAM params)
{
    m_radioParams->loadModel(params);
    m_ui->tableParams->repaint();
}

// Слот вызывается при отжатии кнопки мыши с объекта
void MainForm::slotMouseRelease(const RadioId & radioItemId)
{
    static ConnectionManager & connectionManager = ConnectionManager::instance();
    connectionManager.updateTopologyFor(radioItemId);
}
