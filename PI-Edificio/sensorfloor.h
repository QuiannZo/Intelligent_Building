#ifndef SENSORFLOOR_H
#define SENSORFLOOR_H

#include <QMainWindow>

namespace Ui {
class SensorFloor;
}

class SensorFloor : public QMainWindow
{
    Q_OBJECT

public:
    explicit SensorFloor(QWidget *parent = nullptr);
    ~SensorFloor();

private:
    Ui::SensorFloor *ui;
};

#endif // SENSORFLOOR_H
