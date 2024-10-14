#ifndef SENSORBUILDING_H
#define SENSORBUILDING_H

#include <QMainWindow>

namespace Ui {
class sensorBuilding;
}

class sensorBuilding : public QMainWindow
{
    Q_OBJECT

public:
    explicit sensorBuilding(QWidget *parent = nullptr);
    ~sensorBuilding();

private:
    Ui::sensorBuilding *ui;
};

#endif // SENSORBUILDING_H
