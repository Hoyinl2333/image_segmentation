/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *adaptHeightHction;
    QAction *adaptWidthAction;
    QAction *initAction;
    QAction *inputAction;
    QAction *outputAction;
    QAction *setOriginSizeAction;
    QAction *startAction;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *lblImgOrigin;
    QTextEdit *textEdit;
    QTabWidget *tabWidget;
    QWidget *RNAM;
    QGridLayout *gridLayout_2;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_RNAM_epsilon;
    QLabel *label_2;
    QComboBox *comboBox_RNAM_segMethod;
    QSpacerItem *horizontalSpacer;
    QLabel *lbl_RNAM_segmentation;
    QLabel *lbl_RNAM_compression;
    QWidget *STC;
    QGridLayout *gridLayout;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBox_STC_epsilon;
    QLabel *label_13;
    QComboBox *comboBox_STC_segMethod;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lbl_STC_segmentation;
    QLabel *lbl_STC_compression;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(638, 481);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/12.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        adaptHeightHction = new QAction(MainWindow);
        adaptHeightHction->setObjectName("adaptHeightHction");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/images/07.png"), QSize(), QIcon::Normal, QIcon::Off);
        adaptHeightHction->setIcon(icon1);
        adaptHeightHction->setMenuRole(QAction::NoRole);
        adaptWidthAction = new QAction(MainWindow);
        adaptWidthAction->setObjectName("adaptWidthAction");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/images/06.png"), QSize(), QIcon::Normal, QIcon::Off);
        adaptWidthAction->setIcon(icon2);
        adaptWidthAction->setMenuRole(QAction::NoRole);
        initAction = new QAction(MainWindow);
        initAction->setObjectName("initAction");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/images/01.png"), QSize(), QIcon::Normal, QIcon::Off);
        initAction->setIcon(icon3);
        initAction->setMenuRole(QAction::NoRole);
        inputAction = new QAction(MainWindow);
        inputAction->setObjectName("inputAction");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/images/02.png"), QSize(), QIcon::Normal, QIcon::Off);
        inputAction->setIcon(icon4);
        inputAction->setMenuRole(QAction::NoRole);
        outputAction = new QAction(MainWindow);
        outputAction->setObjectName("outputAction");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/images/03.png"), QSize(), QIcon::Normal, QIcon::Off);
        outputAction->setIcon(icon5);
        outputAction->setMenuRole(QAction::NoRole);
        setOriginSizeAction = new QAction(MainWindow);
        setOriginSizeAction->setObjectName("setOriginSizeAction");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/images/08.png"), QSize(), QIcon::Normal, QIcon::Off);
        setOriginSizeAction->setIcon(icon6);
        setOriginSizeAction->setMenuRole(QAction::NoRole);
        startAction = new QAction(MainWindow);
        startAction->setObjectName("startAction");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/images/05.png"), QSize(), QIcon::Normal, QIcon::Off);
        startAction->setIcon(icon7);
        startAction->setMenuRole(QAction::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(300, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblImgOrigin = new QLabel(frame);
        lblImgOrigin->setObjectName("lblImgOrigin");
        lblImgOrigin->setMinimumSize(QSize(200, 200));
        lblImgOrigin->setFrameShape(QFrame::Box);
        lblImgOrigin->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblImgOrigin);

        textEdit = new QTextEdit(frame);
        textEdit->setObjectName("textEdit");
        textEdit->setMinimumSize(QSize(0, 200));
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);

        horizontalLayout->addWidget(frame);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        RNAM = new QWidget();
        RNAM->setObjectName("RNAM");
        gridLayout_2 = new QGridLayout(RNAM);
        gridLayout_2->setObjectName("gridLayout_2");
        frame_2 = new QFrame(RNAM);
        frame_2->setObjectName("frame_2");
        frame_2->setMinimumSize(QSize(0, 0));
        frame_2->setMaximumSize(QSize(16777215, 100));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        doubleSpinBox_RNAM_epsilon = new QDoubleSpinBox(frame_2);
        doubleSpinBox_RNAM_epsilon->setObjectName("doubleSpinBox_RNAM_epsilon");
        doubleSpinBox_RNAM_epsilon->setMinimumSize(QSize(100, 0));
        doubleSpinBox_RNAM_epsilon->setDecimals(1);

        horizontalLayout_2->addWidget(doubleSpinBox_RNAM_epsilon);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        comboBox_RNAM_segMethod = new QComboBox(frame_2);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/images/11.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox_RNAM_segMethod->addItem(icon8, QString());
        comboBox_RNAM_segMethod->setObjectName("comboBox_RNAM_segMethod");
        comboBox_RNAM_segMethod->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(comboBox_RNAM_segMethod);

        horizontalSpacer = new QSpacerItem(202, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout_2->addWidget(frame_2, 0, 0, 1, 2);

        lbl_RNAM_segmentation = new QLabel(RNAM);
        lbl_RNAM_segmentation->setObjectName("lbl_RNAM_segmentation");
        lbl_RNAM_segmentation->setMinimumSize(QSize(200, 200));
        lbl_RNAM_segmentation->setFrameShape(QFrame::Box);
        lbl_RNAM_segmentation->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_RNAM_segmentation, 1, 0, 1, 1);

        lbl_RNAM_compression = new QLabel(RNAM);
        lbl_RNAM_compression->setObjectName("lbl_RNAM_compression");
        lbl_RNAM_compression->setMinimumSize(QSize(200, 200));
        lbl_RNAM_compression->setFrameShape(QFrame::Box);
        lbl_RNAM_compression->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_RNAM_compression, 1, 1, 1, 1);

        tabWidget->addTab(RNAM, QString());
        STC = new QWidget();
        STC->setObjectName("STC");
        gridLayout = new QGridLayout(STC);
        gridLayout->setObjectName("gridLayout");
        frame_4 = new QFrame(STC);
        frame_4->setObjectName("frame_4");
        frame_4->setMaximumSize(QSize(16777215, 100));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_4);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_10 = new QLabel(frame_4);
        label_10->setObjectName("label_10");
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_10);

        doubleSpinBox_STC_epsilon = new QDoubleSpinBox(frame_4);
        doubleSpinBox_STC_epsilon->setObjectName("doubleSpinBox_STC_epsilon");
        doubleSpinBox_STC_epsilon->setMinimumSize(QSize(100, 0));
        doubleSpinBox_STC_epsilon->setDecimals(1);

        horizontalLayout_4->addWidget(doubleSpinBox_STC_epsilon);

        label_13 = new QLabel(frame_4);
        label_13->setObjectName("label_13");
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_13);

        comboBox_STC_segMethod = new QComboBox(frame_4);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/images/09.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox_STC_segMethod->addItem(icon9, QString());
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/images/10.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox_STC_segMethod->addItem(icon10, QString());
        comboBox_STC_segMethod->setObjectName("comboBox_STC_segMethod");
        comboBox_STC_segMethod->setMinimumSize(QSize(100, 0));

        horizontalLayout_4->addWidget(comboBox_STC_segMethod);

        horizontalSpacer_2 = new QSpacerItem(90, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        gridLayout->addWidget(frame_4, 0, 0, 1, 2);

        lbl_STC_segmentation = new QLabel(STC);
        lbl_STC_segmentation->setObjectName("lbl_STC_segmentation");
        lbl_STC_segmentation->setMinimumSize(QSize(200, 200));
        lbl_STC_segmentation->setFrameShape(QFrame::Box);
        lbl_STC_segmentation->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl_STC_segmentation, 1, 0, 1, 1);

        lbl_STC_compression = new QLabel(STC);
        lbl_STC_compression->setObjectName("lbl_STC_compression");
        lbl_STC_compression->setMinimumSize(QSize(200, 200));
        lbl_STC_compression->setFrameShape(QFrame::Box);
        lbl_STC_compression->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl_STC_compression, 1, 1, 1, 1);

        tabWidget->addTab(STC, QString());

        horizontalLayout->addWidget(tabWidget);

        horizontalLayout->setStretch(0, 1);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        toolBar->addAction(initAction);
        toolBar->addAction(inputAction);
        toolBar->addAction(outputAction);
        toolBar->addAction(startAction);
        toolBar->addSeparator();
        toolBar->addAction(adaptWidthAction);
        toolBar->addAction(adaptHeightHction);
        toolBar->addAction(setOriginSizeAction);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        adaptHeightHction->setText(QCoreApplication::translate("MainWindow", "\345\220\210\351\200\202\351\253\230\345\272\246", nullptr));
#if QT_CONFIG(tooltip)
        adaptHeightHction->setToolTip(QCoreApplication::translate("MainWindow", "\350\260\203\346\225\264\345\233\276\347\211\207\350\207\263\345\220\210\351\200\202\351\253\230\345\272\246", nullptr));
#endif // QT_CONFIG(tooltip)
        adaptWidthAction->setText(QCoreApplication::translate("MainWindow", "\345\220\210\351\200\202\345\256\275\345\272\246", nullptr));
#if QT_CONFIG(tooltip)
        adaptWidthAction->setToolTip(QCoreApplication::translate("MainWindow", "\350\260\203\346\225\264\345\233\276\347\211\207\350\207\263\345\220\210\351\200\202\345\256\275\345\272\246", nullptr));
#endif // QT_CONFIG(tooltip)
        initAction->setText(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226", nullptr));
        inputAction->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\345\233\276\347\211\207", nullptr));
#if QT_CONFIG(tooltip)
        inputAction->setToolTip(QCoreApplication::translate("MainWindow", "\344\273\216\346\234\254\345\234\260\345\257\274\345\205\245\345\233\276\347\211\207", nullptr));
#endif // QT_CONFIG(tooltip)
        outputAction->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272", nullptr));
#if QT_CONFIG(tooltip)
        outputAction->setToolTip(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\345\233\276\347\211\207\345\222\214\346\234\211\345\205\263\344\277\241\346\201\257\350\207\263\346\234\254\345\234\260", nullptr));
#endif // QT_CONFIG(tooltip)
        setOriginSizeAction->setText(QCoreApplication::translate("MainWindow", "\345\216\237\345\247\213\345\244\247\345\260\217", nullptr));
#if QT_CONFIG(tooltip)
        setOriginSizeAction->setToolTip(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\345\233\276\347\211\207\345\216\237\345\247\213\345\244\247\345\260\217", nullptr));
#endif // QT_CONFIG(tooltip)
        startAction->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
#if QT_CONFIG(tooltip)
        startAction->setToolTip(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214\347\250\213\345\272\217", nullptr));
#endif // QT_CONFIG(tooltip)
        lblImgOrigin->setText(QCoreApplication::translate("MainWindow", "\345\216\237\345\233\276\345\203\217\346\230\276\347\244\272\345\214\272", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\220\214\347\261\273\345\235\227\351\230\210\345\200\274", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\210\206\345\211\262\346\226\271\346\263\225", nullptr));
        comboBox_RNAM_segMethod->setItemText(0, QCoreApplication::translate("MainWindow", "\345\257\271\350\247\222\347\272\277\346\263\225", nullptr));

        lbl_RNAM_segmentation->setText(QCoreApplication::translate("MainWindow", "\345\210\206\345\211\262\347\273\223\346\236\234\346\230\276\347\244\272\345\214\272", nullptr));
        lbl_RNAM_compression->setText(QCoreApplication::translate("MainWindow", "\345\216\213\347\274\251\345\233\276\345\203\217\346\230\276\347\244\272\345\214\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(RNAM), QCoreApplication::translate("MainWindow", "RNAM", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\345\220\214\347\261\273\345\235\227\351\230\210\345\200\274", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\345\210\206\345\211\262\346\226\271\346\263\225", nullptr));
        comboBox_STC_segMethod->setItemText(0, QCoreApplication::translate("MainWindow", "\345\236\202\347\233\264", nullptr));
        comboBox_STC_segMethod->setItemText(1, QCoreApplication::translate("MainWindow", "\346\260\264\345\271\263", nullptr));

        lbl_STC_segmentation->setText(QCoreApplication::translate("MainWindow", "\345\210\206\345\211\262\347\273\223\346\236\234\346\230\276\347\244\272\345\214\272", nullptr));
        lbl_STC_compression->setText(QCoreApplication::translate("MainWindow", "\345\216\213\347\274\251\345\233\276\345\203\217\346\230\276\347\244\272\345\214\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(STC), QCoreApplication::translate("MainWindow", "STC", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
