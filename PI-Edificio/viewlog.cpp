#include "viewlog.h"
#include "ui_viewlog.h"

viewLog::viewLog(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::viewLog)
{
    ui->setupUi(this);

    //Fondos para los widgets y mainw.
    // Load background.
    QPalette palette;
    QPixmap bkgnd(":/resource/img/build.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    palette.setBrush(QPalette::Window, bkgnd);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

}

viewLog::~viewLog()
{
    delete ui;
}
