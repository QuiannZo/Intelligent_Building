#ifndef VIEWLOG_H
#define VIEWLOG_H

#include <QMainWindow>
#include "../UserHandler.hpp"
#include "menuwindow.h"

namespace Ui {
class viewLog;
}

class viewLog : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewLog(QWidget *parent, UserHandler& userHandler, menuwindow& menu);
    ~viewLog();

private slots:
    void on_pushButton1_2_clicked();

private:
    Ui::viewLog *ui;
    UserHandler& userHandler;
    menuwindow& menu;
};

#endif // VIEWLOG_H
