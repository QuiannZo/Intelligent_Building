#ifndef VIEWBACKUP_H
#define VIEWBACKUP_H

#include <QMainWindow>
#include "../etapa4/etapa4PI/UserNode.hpp"
#include "menuwindow.h"

namespace Ui {
class ViewBackup;
}

class ViewBackup : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewBackup(QWidget *parent, UserNode& userHandler, menuwindow& menu, ClientNode& clientNode);
    ~ViewBackup();

private slots:
    void on_pushButton1_2_clicked();

    void on_backupbtn_clicked();

private:
    Ui::ViewBackup *ui;
    UserNode& userHandler;
    menuwindow& menu;
    ClientNode& clientNode;
};

#endif // VIEWBACKUP_H
