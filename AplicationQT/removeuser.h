#ifndef REMOVEUSER_H
#define REMOVEUSER_H

#include <QMainWindow>
#include "../etapa4/etapa4PI/UserNode.hpp"
#include "menuwindow.h"
#include "qlistwidget.h"
#include <qfile.h>
#include <QMessageBox>

namespace Ui {
class RemoveUser;
}

class RemoveUser : public QMainWindow
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit RemoveUser(QWidget *parent, UserNode& userHandler, menuwindow& menu, ClientNode& clientNode);
=======
    explicit RemoveUser(QWidget *parent, UserNode& userHandler, menuwindow& menu);
>>>>>>> refs/remotes/origin/main
    ~RemoveUser();

private slots:
    void on_pushButton1_2_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void loadUserList();

    void on_pushButton1_clicked();

private:
    Ui::RemoveUser *ui;
    UserNode& userHandler;
    menuwindow& menu;
    QString selectedUser;
    ClientNode& clientNode;
};

#endif // REMOVEUSER_H
