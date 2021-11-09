#ifndef SECONDSCREEN_H
#define SECONDSCREEN_H

#include <QDialog>
#include <qcustomplot.h>

namespace Ui {
class SecondScreen;
}

class SecondScreen : public QDialog
{
    Q_OBJECT

public:
    explicit SecondScreen(QWidget *parent = nullptr);
    ~SecondScreen();

    void setupCircle();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SecondScreen *ui;
    QCPCurve *newCurve;

};

#endif // SECONDSCREEN_H
