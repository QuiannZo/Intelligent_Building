#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "viewdatabasewindow.h"
#include "viewuser.h"
#include "createuser.h"
#include "viewlog.h"
#include "removeuser.h"
#include "modifyuser.h"
#include "modifydatabase.h"
#include "viewlog.h"
#include "viewnode.h"
#include "sensorfloor.h"
#include "sensorbuilding.h"
#include "viewbackup.h"

menuwindow::menuwindow(QWidget *parent, UserHandler *userHandler)
    : QMainWindow(parent), userHandler(userHandler)
    , ui(new Ui::menuwindow)
{
    ui->setupUi(this);

    //Fondos para los widgets y mainw.
    // Load background.
    QPalette palette;
    QPixmap bkgnd(":/resource/img/a1.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    palette.setBrush(QPalette::Window, bkgnd);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    // menuwidget.
    QString path2 = ":/resource/img/primary.jpeg";
    QPixmap bkgnd2(path2);

    if (!bkgnd2.isNull()) {
        bkgnd2 = bkgnd2.scaled(ui->menuwidget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd2);
        ui->menuwidget->setAutoFillBackground(true);
        ui->menuwidget->setPalette(palette);
    } else {
        qDebug() << "Error: no se pudo cargar la imagen";
    }

    QPalette palette2;
    palette2.setBrush(QPalette::Window, bkgnd2);
    ui->menuwidget->setAutoFillBackground(true);
    ui->menuwidget->setPalette(palette2);

    // Botones.
    // icono y el texto
    QString path3 = ":/resource/img/database.png";
    ui->pushButton->setIcon(QIcon(path3));
    ui->pushButton->setIconSize(QSize(48, 48));

    path3 = ":/resource/img/database.png";
    ui->pushButton2->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton2->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = ":/resource/img/sensor.png";
    ui->pushButton3->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton3->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = ":/resource/img/user.png";
    ui->pushButton4->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton4->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = ":/resource/img/group.png";
    ui->pushButton5->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton5->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = ":/resource/img/add-user.png";
    ui->pushButton6->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton6->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = ":/resource/img/remove-user.png";
    ui->pushButton7->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton7->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = ":/resource/img/sensor.png";
    ui->pushButton8->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton8->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = ":/resource/img/document.png";
    ui->pushButton9->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton9->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = ":/resource/img/database (1).png";
    ui->pushButton10->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton10->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = ":/resource/img/document.png";
    ui->pushButton11->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton11->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono
}

menuwindow::~menuwindow()
{
    delete ui;
}

void menuwindow::on_pushButton_clicked()
{
    viewdatabasewindow *databaseWindow = new viewdatabasewindow(this);  // Crear la nueva ventana
    databaseWindow->show();  // Mostrar la nueva ventana
    hide();
}


/*void menuwindow::on_pushButton4_clicked()
{
    ViewUser *viewUser = new ViewUser(this);  // Crear la nueva ventana
    viewUser->show();  // Mostrar la nueva ventana
    hide();
}*/


void menuwindow::on_pushButton6_clicked()
{
    createuser *createUser = new createuser(this, this->userHandler);  // Crear la nueva ventana
    createUser->show();  // Mostrar la nueva ventana
    hide();
}


/*void menuwindow::on_pushButton11_clicked()
{
    viewLog *viewlog = new viewLog(this);  // Crear la nueva ventana
    viewlog->show();  // Mostrar la nueva ventana
    hide();
}*/


void menuwindow::on_pushButton7_clicked()
{
    RemoveUser *removeuser = new RemoveUser(this);  // Crear la nueva ventana
    removeuser->show();  // Mostrar la nueva ventana
    hide();
}


void menuwindow::on_pushButton5_clicked()
{
    ModifyUser *modifyUser = new ModifyUser(this);  // Crear la nueva ventana
    modifyUser->show();  // Mostrar la nueva ventana
    hide();
}


void menuwindow::on_pushButton2_clicked()
{
    ModifyDataBase *modifyData = new ModifyDataBase(this);  // Crear la nueva ventana
    modifyData->show();  // Mostrar la nueva ventana
    hide();
}

void menuwindow::on_pushButton3_clicked()
{
    SensorFloor *sensorFloor = new SensorFloor(this); // Crear la nueva ventana
    sensorFloor->show();                              // Mostrar la nueva ventana
    hide();
}

void menuwindow::on_pushButton4_clicked()
{
    ViewUser *viewUser = new ViewUser(this); // Crear la nueva ventana
    viewUser->show();                        // Mostrar la nueva ventana
    hide();
}

void menuwindow::on_pushButton8_clicked()
{
    sensorBuilding *building = new sensorBuilding(this); // Crear la nueva ventana
    building->show();                                    // Mostrar la nueva ventana
    hide();
}

void menuwindow::on_pushButton9_clicked()
{
    ViewNode *viewNode = new ViewNode(this); // Crear la nueva ventana
    viewNode->show();                        // Mostrar la nueva ventana
    hide();
}

void menuwindow::on_pushButton10_clicked()
{
    ViewBackup *viewBackup = new ViewBackup(this); // Crear la nueva ventana
    viewBackup->show();                            // Mostrar la nueva ventana
    hide();
}

void menuwindow::on_pushButton11_clicked()
{
    viewLog *log = new viewLog(this); // Crear la nueva ventana
    log->show();                      // Mostrar la nueva ventana
    hide();
}
