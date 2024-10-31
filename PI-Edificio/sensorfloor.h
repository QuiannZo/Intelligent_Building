#ifndef SENSORFLOOR_H
#define SENSORFLOOR_H

#include <QMainWindow>
#include "../UserHandler.hpp"
#include "menuwindow.h"

namespace Ui {
class SensorFloor;
}

class SensorFloor : public QMainWindow
{
    Q_OBJECT

public:
    explicit SensorFloor(QWidget *parent, UserHandler& userHandler, menuwindow& menu);
    ~SensorFloor();

private slots:
    void on_pushButton1_2_clicked();

private:
    Ui::SensorFloor *ui;
    UserHandler& userHandler;
    menuwindow& menu;
};

#endif // SENSORFLOOR_H
