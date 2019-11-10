/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *batteryButton;
    QPushButton *resistanceButton;
    QPushButton *motorButton;
    QPushButton *bulbButton;
    QPushButton *wireButton;
    QLabel *backgroundLabel;
    QCheckBox *checkBox;
    QLabel *label;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(761, 687);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        batteryButton = new QPushButton(centralWidget);
        batteryButton->setObjectName(QString::fromUtf8("batteryButton"));
        batteryButton->setGeometry(QRect(0, 0, 171, 71));
        resistanceButton = new QPushButton(centralWidget);
        resistanceButton->setObjectName(QString::fromUtf8("resistanceButton"));
        resistanceButton->setGeometry(QRect(160, 0, 171, 71));
        motorButton = new QPushButton(centralWidget);
        motorButton->setObjectName(QString::fromUtf8("motorButton"));
        motorButton->setGeometry(QRect(320, 0, 171, 71));
        bulbButton = new QPushButton(centralWidget);
        bulbButton->setObjectName(QString::fromUtf8("bulbButton"));
        bulbButton->setGeometry(QRect(480, 0, 171, 71));
        wireButton = new QPushButton(centralWidget);
        wireButton->setObjectName(QString::fromUtf8("wireButton"));
        wireButton->setGeometry(QRect(640, 0, 121, 71));
        wireButton->setCheckable(true);
        backgroundLabel = new QLabel(centralWidget);
        backgroundLabel->setObjectName(QString::fromUtf8("backgroundLabel"));
        backgroundLabel->setGeometry(QRect(10, 70, 741, 581));
        backgroundLabel->setAutoFillBackground(true);
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(10, 630, 91, 20));
        checkBox->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 630, 81, 16));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ELEC Laboratory", nullptr));
        batteryButton->setText(QCoreApplication::translate("MainWindow", "Battery", nullptr));
        resistanceButton->setText(QCoreApplication::translate("MainWindow", "Resistor", nullptr));
        motorButton->setText(QCoreApplication::translate("MainWindow", "Motor", nullptr));
        bulbButton->setText(QCoreApplication::translate("MainWindow", "Light Bulb", nullptr));
        wireButton->setText(QCoreApplication::translate("MainWindow", "Wire", nullptr));
        backgroundLabel->setText(QString());
        checkBox->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:300; color:#000000;\">DisplayInfo</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
