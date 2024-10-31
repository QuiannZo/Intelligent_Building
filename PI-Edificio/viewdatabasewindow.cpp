#include "viewdatabasewindow.h"
#include "ui_viewdatabasewindow.h"

viewdatabasewindow::viewdatabasewindow(QWidget *parent, UserHandler& userHandler, menuwindow& menu) :
    QMainWindow(parent),
    ui(new Ui::viewdatabasewindow), userHandler(userHandler), menu(menu)
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

    // Botones.
    // icono y el texto
    QString path3 = ":/resource/img/sensor.png";
    ui->pushButton8->setIcon(QIcon(path3));
    ui->pushButton8->setIconSize(QSize(48, 48));

    path3 = ":/resource/img/document.png";
    ui->pushButton8_2->setIcon(QIcon(path3));
    ui->pushButton8_2->setIconSize(QSize(48, 48));

    path3 = ":/resource/img/sensor.png";
    ui->pushButton8_3->setIcon(QIcon(path3));
    ui->pushButton8_3->setIconSize(QSize(48, 48));

}
viewdatabasewindow::~viewdatabasewindow()
{
    delete ui;
}


void viewdatabasewindow::on_pushButton1_2_clicked()
{
    this->menu.show();
    this->hide();
    this->deleteLater();
}


void viewdatabasewindow::on_pushButton8_clicked() // Sensor building
{

}


void viewdatabasewindow::on_pushButton8_2_clicked() // Node information
{

}


void viewdatabasewindow::on_pushButton8_3_clicked() // Sensor floor
{

}

