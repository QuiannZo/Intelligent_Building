#include "createuser.h"
#include "ui_createuser.h"

createuser::createuser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::createuser)
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
    QString path2 = ":/resource/img/add-user.png";
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
                              "color: #FFFFFF; }");

    // contraseña label
    ui->contrasena->setStyleSheet("QLabel { "
                              "color: #FFFFFF; }");

    // rol label
    ui->rol->setStyleSheet("QLabel { "
                              "color: #FFFFFF; }");


}

createuser::~createuser()
{
    delete ui;
}
