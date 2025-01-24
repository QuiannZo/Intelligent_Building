#ifndef MODIFYUSER_H
#define MODIFYUSER_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "../etapa4/etapa4PI/UserNode.hpp"
<<<<<<< HEAD
#include "../etapa4/etapa4PI/ClientNode.hpp"
=======
>>>>>>> refs/remotes/origin/main
#include "menuwindow.h"

namespace Ui {
class ModifyUser;
}

class ModifyUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModifyUser(QWidget *parent, UserNode& userHandler, menuwindow& menu, ClientNode& clientNode);
    ~ModifyUser();

private slots:
    void on_pushButton1_clicked();

    void on_pushButton1_2_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void loadUserList();

    std::string checkPermissions(uint8_t user_permissions);

private:
    Ui::ModifyUser *ui;
    UserNode& userHandler;
    menuwindow& menu;
    ClientNode& clientNode;
    std::string selectedUsername;
};

#endif // MODIFYUSER_H
