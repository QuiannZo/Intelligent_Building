#ifndef VIEWLOG_H
#define VIEWLOG_H

#include <QMainWindow>
#include <QString>
#include "../UserHandler.hpp"
#include "../etapa3PI/ClientNode.hpp"
#include "menuwindow.h"

namespace Ui {
class viewLog;
}

class viewLog : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewLog(QWidget *parent, UserHandler& userHandler, menuwindow& menu, ClientNode& clientNode);
    ~viewLog();

private slots:
    void on_pushButton1_2_clicked();

    void on_datanodebtn_clicked();

    void on_interlogbtn_clicked();

    void on_userlogbtn_clicked();

private:
    Ui::viewLog *ui;
    UserHandler& userHandler;
    menuwindow& menu;
    ClientNode& clientNode;
};

#endif // VIEWLOG_H
