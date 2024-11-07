#ifndef REMOVEUSER_H
#define REMOVEUSER_H

#include <QMainWindow>
#include "../UserHandler.hpp"
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
    explicit RemoveUser(QWidget *parent, UserHandler& userHandler, menuwindow& menu);
    ~RemoveUser();

private slots:
    void on_pushButton1_2_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void loadUserList();

    void on_pushButton1_clicked();

private:
    Ui::RemoveUser *ui;
    UserHandler& userHandler;
    menuwindow& menu;
    QString selectedUser;
};

#endif // REMOVEUSER_H
