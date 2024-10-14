#include "sensorbuilding.h"
#include "ui_sensorbuilding.h"

sensorBuilding::sensorBuilding(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::sensorBuilding)
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

sensorBuilding::~sensorBuilding()
{
    delete ui;
}
