#include "viewuser.h"
#include "ui_viewuser.h"

ViewUser::ViewUser(QWidget *parent, UserHandler& userHandler, menuwindow& menu)
    : QMainWindow(parent)
    , ui(new Ui::ViewUser), userHandler(userHandler), menu(menu)
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

    // userWidget
    QString path2 = ":/resource/img/user.png";
    QPixmap bkgnd2(path2);

    if (!bkgnd2.isNull()) {
        bkgnd2 = bkgnd2.scaled(ui->widgetUser->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd2);
        ui->widgetUser->setAutoFillBackground(true);
        ui->widgetUser->setPalette(palette);
    } else {
        qDebug() << "Error: no se pudo cargar la imagen";
    }

    // nombre label
    ui->nombre->setStyleSheet("QLabel { "
                              "background-color: #FFFFFF; "
                              "color: #000000; }");

    // apellido label
    ui->apellido->setStyleSheet("QLabel { "
                                "background-color: #FFFFFF; "
                                "color: #000000; }");

    // rol label
    ui->rol->setStyleSheet("QLabel { "
                           "background-color: #FFFFFF; "
                           "color: #000000; }");

    // ultimaActividad label
    ui->ultimaActividad->setStyleSheet("QLabel { "
                           "background-color: #FFFFFF; "
                           "color: #000000; }");
}

ViewUser::~ViewUser()
{
    delete ui;
}

void ViewUser::on_pushButton1_2_clicked()
{
    this->menu.show();
    this->hide();
    this->deleteLater();
}

