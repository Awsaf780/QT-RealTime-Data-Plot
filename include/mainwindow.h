#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <time.h>
#include "secondscreen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupPlot();


private slots:

    void realtimeDataSlot();

    void on_pushButton_clicked();

    void on_voltage_1_stateChanged(int arg1);

    void on_voltage_0_stateChanged(int arg1);

    void on_voltage_2_stateChanged(int arg1);

    void on_adc_toggle_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    SecondScreen *second;
    QTimer *dataTimer;
    int num;

    bool volt_0;
    bool volt_1;
    bool volt_2;

    int ADCRange;
    int volt_range;

};
#endif // MAINWINDOW_H
