#include "sensorfloor.h"
#include "ui_sensorfloor.h"

SensorFloor::SensorFloor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SensorFloor)
{
    ui->setupUi(this);

    // Load background
    QPalette palette;
    QPixmap bkgnd(":/resource/img/build.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    palette.setBrush(QPalette::Window, bkgnd);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

SensorFloor::~SensorFloor()
{
    delete ui;
}
