#ifndef VIEWDATABASEWINDOW_H
#define VIEWDATABASEWINDOW_H

#include <QMainWindow>
#include <QFile>
#include "../etapa4/etapa4PI/UserNode.hpp"
<<<<<<< HEAD
#include "../etapa3PI/ClientNode.hpp"
=======
>>>>>>> refs/remotes/origin/main
#include "menuwindow.h"

namespace Ui {
class viewdatabasewindow;
}

class viewdatabasewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewdatabasewindow(QWidget *parent, UserNode& userHandler, menuwindow& menu, ClientNode& clientNode);
    ~viewdatabasewindow();

private slots:
    void on_pushButton1_2_clicked();

    void on_pushButton8_clicked();

private:
    Ui::viewdatabasewindow *ui;
    UserNode& userHandler;
    menuwindow& menu;
    ClientNode& clientNode;
};

#endif // VIEWDATABASEWINDOW_H
