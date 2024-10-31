#ifndef VIEWUSER_H
#define VIEWUSER_H

#include <QMainWindow>
#include "../UserHandler.hpp"
#include "menuwindow.h"

namespace Ui {
class ViewUser;
}

class ViewUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewUser(QWidget *parent, UserHandler& userHandler, menuwindow& menu);
    ~ViewUser();

private slots:
    void on_pushButton1_2_clicked();

private:
    Ui::ViewUser *ui;
    UserHandler& userHandler;
    menuwindow& menu;
};

#endif // VIEWUSER_H
