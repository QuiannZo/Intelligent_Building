#ifndef MODIFYUSER_H
#define MODIFYUSER_H

#include <QMainWindow>
#include "../UserHandler.hpp"
#include "menuwindow.h"

namespace Ui {
class ModifyUser;
}

class ModifyUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModifyUser(QWidget *parent, UserHandler& userHandler, menuwindow& menu);
    ~ModifyUser();

private slots:
    void on_pushButton1_clicked();

    void on_pushButton1_2_clicked();

private:
    Ui::ModifyUser *ui;
    UserHandler& userHandler;
    menuwindow& menu;
};

#endif // MODIFYUSER_H
