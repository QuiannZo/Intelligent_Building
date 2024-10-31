#ifndef VIEWBACKUP_H
#define VIEWBACKUP_H

#include <QMainWindow>
#include "../UserHandler.hpp"
#include "menuwindow.h"

namespace Ui {
class ViewBackup;
}

class ViewBackup : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewBackup(QWidget *parent, UserHandler& userHandler, menuwindow& menu);
    ~ViewBackup();

private slots:
    void on_pushButton1_2_clicked();

private:
    Ui::ViewBackup *ui;
    UserHandler& userHandler;
    menuwindow& menu;
};

#endif // VIEWBACKUP_H
