#ifndef VIEWUSER_H
#define VIEWUSER_H

#include <QMainWindow>
#include <QFile>
#include "../UserHandler.hpp"
#include "menuwindow.h"
#include "qlistwidget.h"

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

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void loadUserList();

private:
    Ui::ViewUser *ui;
    UserHandler& userHandler;
    menuwindow& menu;
};

#endif // VIEWUSER_H
