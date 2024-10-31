#ifndef VIEWDATABASEWINDOW_H
#define VIEWDATABASEWINDOW_H

#include <QMainWindow>
#include <QFile>
#include "../UserHandler.hpp"
#include "menuwindow.h"

namespace Ui {
class viewdatabasewindow;
}

class viewdatabasewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewdatabasewindow(QWidget *parent, UserHandler& userHandler, menuwindow& menu);
    ~viewdatabasewindow();

private slots:
    void on_pushButton1_2_clicked();

    void on_pushButton8_clicked();

    void on_pushButton8_2_clicked();

    void on_pushButton8_3_clicked();

private:
    Ui::viewdatabasewindow *ui;
    UserHandler& userHandler;
    menuwindow& menu;
};

#endif // VIEWDATABASEWINDOW_H
