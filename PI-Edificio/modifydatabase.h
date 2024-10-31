#ifndef MODIFYDATABASE_H
#define MODIFYDATABASE_H

#include <QMainWindow>
#include "../UserHandler.hpp"
#include "menuwindow.h"

namespace Ui {
class ModifyDataBase;
}

class ModifyDataBase : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModifyDataBase(QWidget *parent, UserHandler& userHandler, menuwindow& menu);
    ~ModifyDataBase();

private slots:
    void on_pushButton1_2_clicked();

private:
    Ui::ModifyDataBase *ui;
    UserHandler& userHandler;
    menuwindow& menu;
};

#endif // MODIFYDATABASE_H
