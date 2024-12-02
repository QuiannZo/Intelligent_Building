#ifndef VIEWUSER_H
#define VIEWUSER_H

#include <QMainWindow>
#include <QFile>
#include <qstring.h>
#include "../etapa4/etapa4PI/UserNode.hpp"
<<<<<<< HEAD
#include "../etapa4/etapa4PI/ClientNode.hpp"
=======
>>>>>>> refs/remotes/origin/main
#include "menuwindow.h"
#include "qlistwidget.h"

namespace Ui {
class ViewUser;
}

class ViewUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewUser(QWidget *parent, UserNode& userHandler, menuwindow& menu, ClientNode& clientNode);
    ~ViewUser();

private slots:
    void on_pushButton1_2_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void loadUserList();

    std::string checkPermissions(uint8_t user_permissions);

private:
    Ui::ViewUser *ui;
    UserNode& userHandler;
    ClientNode& clientNode;
    menuwindow& menu;
};

#endif // VIEWUSER_H
