#include "removeuser.h"
#include "ui_removeuser.h"

RemoveUser::RemoveUser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RemoveUser)
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
    QString path2 = ":/resource/img/remove-user.png";
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
}

RemoveUser::~RemoveUser()
{
    delete ui;
}
