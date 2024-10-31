#ifndef REMOVEUSER_H
#define REMOVEUSER_H

#include <QMainWindow>
#include "../UserHandler.hpp"
#include "menuwindow.h"

namespace Ui {
class RemoveUser;
}

class RemoveUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit RemoveUser(QWidget *parent, UserHandler& userHandler, menuwindow& menu);
    ~RemoveUser();

private slots:
    void on_pushButton1_2_clicked();

private:
    Ui::RemoveUser *ui;
    UserHandler& userHandler;
    menuwindow& menu;
};

#endif // REMOVEUSER_H
