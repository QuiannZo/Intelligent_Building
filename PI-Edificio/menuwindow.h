#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include "../UserHandler.hpp"

namespace Ui {
class menuwindow;
}

class menuwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit menuwindow(QWidget *parent = nullptr, UserHandler *userHandler = nullptr);
    ~menuwindow();

private slots:
    void on_pushButton_clicked();

    //void on_pushButton4_clicked();

    void on_pushButton6_clicked();

   //void on_pushButton11_clicked();

    void on_pushButton7_clicked();

    void on_pushButton5_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();
    void on_pushButton4_clicked();
    void on_pushButton8_clicked();
    void on_pushButton9_clicked();
    void on_pushButton10_clicked();
    void on_pushButton11_clicked();

private:
    Ui::menuwindow *ui;
    UserHandler *userHandler;
};

#endif // MENUWINDOW_H
