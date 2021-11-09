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

private:
    Ui::MainWindow *ui;
    SecondScreen *second;
    QTimer *dataTimer;


};
#endif // MAINWINDOW_H
