#include "secondscreen.h"
#include "ui_secondscreen.h"
#include "mainwindow.h"

SecondScreen::SecondScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondScreen)
{
    ui->setupUi(this);
}

SecondScreen::~SecondScreen()
{
    delete ui;
}

void SecondScreen::on_pushButton_clicked()
{
    hide();

    MainWindow *newmain= new MainWindow();
    newmain->show();
}
