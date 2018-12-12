/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGraphicsView *screen;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QPushButton *btnAddDevice;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QTableView *tableParams;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(800, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        font.setPointSize(12);
        MainForm->setFont(font);
        centralWidget = new QWidget(MainForm);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        screen = new QGraphicsView(centralWidget);
        screen->setObjectName(QString::fromUtf8("screen"));

        gridLayout->addWidget(screen, 0, 0, 1, 1);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 3, 3, 0);
        btnAddDevice = new QPushButton(frame);
        btnAddDevice->setObjectName(QString::fromUtf8("btnAddDevice"));

        verticalLayout->addWidget(btnAddDevice);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        tableParams = new QTableView(frame);
        tableParams->setObjectName(QString::fromUtf8("tableParams"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableParams->sizePolicy().hasHeightForWidth());
        tableParams->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(tableParams);


        gridLayout->addWidget(frame, 0, 1, 1, 1);

        MainForm->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainForm);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 18));
        MainForm->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainForm);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainForm->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainForm);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainForm->setStatusBar(statusBar);

        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QMainWindow *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "MainForm", nullptr));
        btnAddDevice->setText(QApplication::translate("MainForm", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        label->setText(QApplication::translate("MainForm", "\320\241\320\262\320\276\320\271\321\201\321\202\320\262\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
