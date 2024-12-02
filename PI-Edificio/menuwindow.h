#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include "../etapa4/etapa4PI/UserNode.hpp"
#include <QCloseEvent>
#include "mainwindow.h"

namespace Ui {
class menuwindow;
}

class menuwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit menuwindow(QWidget *parent, UserNode& userHandler, MainWindow& mainwindow, ClientNode& clientNode);
    ~menuwindow();

private slots:
    void on_pushButton_clicked();

    //void on_pushButton4_clicked();

    void on_pushButton6_clicked();

   //void on_pushButton11_clicked();

    void on_pushButton7_clicked();

    void on_pushButton5_clicked();

    void on_pushButton3_clicked();
    void on_pushButton4_clicked();
    void on_pushButton8_clicked();
    void on_pushButton9_clicked();
    void on_pushButton10_clicked();
    void on_pushButton11_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::menuwindow *ui;
    UserNode& userHandler;
    MainWindow& mainwindow;
    ClientNode& clientNode;

protected:
    void closeEvent(QCloseEvent *event) override;  // Sobrescribir closeEvent
};

#endif // MENUWINDOW_H
