#ifndef SENSORFLOOR_H
#define SENSORFLOOR_H

#include <QMainWindow>
#include "../etapa4/etapa4PI/UserNode.hpp"
#include "menuwindow.h"

namespace Ui {
class SensorFloor;
}

class SensorFloor : public QMainWindow
{
    Q_OBJECT

public:
    explicit SensorFloor(QWidget *parent, UserNode& userHandler, menuwindow& menu);
    ~SensorFloor();

private slots:
    void on_pushButton1_2_clicked();

private:
    Ui::SensorFloor *ui;
    UserNode& userHandler;
    menuwindow& menu;
};

#endif // SENSORFLOOR_H
