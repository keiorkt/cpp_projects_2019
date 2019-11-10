#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "impl.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_batteryButton_clicked();

    void on_resistanceButton_clicked();

    void on_motorButton_clicked();

    void on_bulbButton_clicked();

    void on_wireButton_toggled(bool checked);

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    Impl *impl;
};

#endif // MAINWINDOW_H
