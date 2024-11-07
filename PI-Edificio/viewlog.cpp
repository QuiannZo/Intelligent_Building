#include "viewlog.h"
#include "ui_viewlog.h"

viewLog::viewLog(QWidget *parent, UserHandler& userHandler, menuwindow& menu)
    : QMainWindow(parent)
    , ui(new Ui::viewLog), userHandler(userHandler), menu(menu)
{
    ui->setupUi(this);

    //Fondos para los widgets y mainw.
    // Load background.
    QPalette palette;
    QPixmap bkgnd(":/resource/img/img1.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    palette.setBrush(QPalette::Window, bkgnd);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

}

viewLog::~viewLog()
{
    delete ui;
}

void viewLog::on_pushButton1_2_clicked()
{
    this->menu.show();
    this->hide();
    this->deleteLater();
}

