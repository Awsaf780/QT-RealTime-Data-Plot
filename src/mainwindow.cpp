#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QObject>
#include<string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupPlot();
//    realtimeDataSlot();
    num = 0;

    volt_0 = true;
    volt_1 = true;
    volt_2 = true;

    ADCRange = 32769;
    ADCRange = 1;

    if (ADCRange == 1){
        volt_range = 3; }
    else{
    volt_range = 50000; }

    ui->voltage_0->toggle();
    ui->voltage_1->toggle();
    ui->voltage_2->toggle();


    ui->customPlot->legend->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::realtimeDataSlot()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;

    // Show time on
    QTime t(QTime::currentTime());
    ui->labelTime->setText(t.toString());

    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      // add data to lines:  
      if(volt_0){
      ui->customPlot->graph(0)->addData(key, ADCRange * qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843)); }

      if(volt_1){
      ui->customPlot->graph(1)->addData(key, ADCRange * qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364)); }

      if(volt_2){
      ui->customPlot->graph(2)->addData(key, ADCRange * qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.2364)); }


        // rescale value (vertical) axis to fit the current data:
//      ui->customPlot->graph(0)->rescaleValueAxis();
//      ui->customPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->customPlot->yAxis->setRange(-1*volt_range, volt_range);

    ui->customPlot->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      ui->statusbar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())

            , 0);
      lastFpsKey = key;
      frameCount = 0;
    }
    }
void MainWindow::setupPlot()
{

    ui->customPlot->addGraph(); // blue line
    ui->customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->customPlot->graph(0)->setName("Voltage 0");

    ui->customPlot->addGraph(); // red line
    ui->customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    ui->customPlot->graph(1)->setName("Voltage 1");

    ui->customPlot->addGraph(); // green line
    ui->customPlot->graph(2)->setPen(QPen(QColor(149, 235, 52)));
    ui->customPlot->graph(2)->setName("Voltage 2");


    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->setRange(-3, 3);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));


    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    dataTimer = new QTimer(this);
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer->start(33); // Interval 0 means to refresh as fast as possible

}


void MainWindow::on_pushButton_clicked()
{
    hide();
    second = new SecondScreen(this);
    second->show();

}

void MainWindow::on_voltage_0_stateChanged(int arg1)
{
    if(arg1==2){
        volt_0 = true;
    }
    else{
        volt_0 = false;
    }
}

void MainWindow::on_voltage_1_stateChanged(int arg1)
{
    if(arg1==2){
        volt_1 = true;
    }
    else{
        volt_1 = false;
    }
}


void MainWindow::on_voltage_2_stateChanged(int arg1)
{
    if(arg1==2){
        volt_2 = true;
    }
    else{
        volt_2 = false;
    }
}

void MainWindow::on_adc_toggle_stateChanged(int arg1)
{
    if(arg1==2){
        ADCRange = 32769;
        volt_range = 50000;
    }
    else{
        ADCRange = 1;
        volt_range = 3;
    }
}
