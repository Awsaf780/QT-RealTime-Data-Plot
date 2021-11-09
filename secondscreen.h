#ifndef SECONDSCREEN_H
#define SECONDSCREEN_H

#include <QDialog>

namespace Ui {
class SecondScreen;
}

class SecondScreen : public QDialog
{
    Q_OBJECT

public:
    explicit SecondScreen(QWidget *parent = nullptr);
    ~SecondScreen();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SecondScreen *ui;

};

#endif // SECONDSCREEN_H
