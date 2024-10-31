#ifndef VIEWNODE_H
#define VIEWNODE_H

#include <QMainWindow>
#include "../UserHandler.hpp"
#include "menuwindow.h"

namespace Ui {
class ViewNode;
}

class ViewNode : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewNode(QWidget *parent, UserHandler& userHandler, menuwindow& menu);
    ~ViewNode();

private slots:
    void on_pushButton1_2_clicked();

private:
    Ui::ViewNode *ui;
    UserHandler& userHandler;
    menuwindow& menu;
};

#endif // VIEWNODE_H
