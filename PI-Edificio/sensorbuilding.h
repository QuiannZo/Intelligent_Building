#ifndef SENSORBUILDING_H
#define SENSORBUILDING_H

#include <QMainWindow>
#include "../etapa4/etapa4PI/UserNode.hpp"
#include "menuwindow.h"

namespace Ui {
class sensorBuilding;
}

class sensorBuilding : public QMainWindow
{
    Q_OBJECT

public:
    explicit sensorBuilding(QWidget *parent, UserNode& userHandler, menuwindow& menu);
    ~sensorBuilding();

private slots:
    void on_pushButton1_2_clicked();

private:
    Ui::sensorBuilding *ui;
    UserNode& userHandler;
    menuwindow& menu;
};

#endif // SENSORBUILDING_H
