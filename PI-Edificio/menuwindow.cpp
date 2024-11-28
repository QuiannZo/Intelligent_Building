#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "viewdatabasewindow.h"
#include "viewuser.h"
#include "createuser.h"
#include "viewlog.h"
#include "removeuser.h"
#include "modifyuser.h"
#include "viewlog.h"
#include "viewnode.h"
#include "sensorfloor.h"
#include "sensorbuilding.h"
#include "viewbackup.h"

menuwindow::menuwindow(QWidget *parent, UserHandler& userHandler, MainWindow& mainwindow, ClientNode& clientNode)
    : QMainWindow(parent), userHandler(userHandler), mainwindow(mainwindow), clientNode(clientNode)
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

    path3 = ":/resource/img/document.png";
    ui->pushButton9->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton9->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = ":/resource/img/database (1).png";
    ui->pushButton10->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton10->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = ":/resource/img/document.png";
    ui->pushButton11->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton11->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    // Obtener los datos del usuario.
    std::vector<std::string> userData;
    clientNode.getUserInformation(clientNode.username, clientNode.username, userData);

    // Permisos.
    QString permission = QString::fromStdString(clientNode.checkPermissions(std::stoi(userData[3])));

    // pushButton view sensor
    // pushButton2 edit database
    // pushButton4 deactivate user
    // pushButton5 view user
    // pushButton6 modify user
    // pushButton7 add user
    // pushButton9 view node information
    // pushButton10 backup state
    // pushButton11 view logs

    if (permission == "User Administrator") {
        ui->pushButton->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton9->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton9->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton10->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton10->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton11->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton11->setStyleSheet("background-color: #888888; color: #AAAAAA;");
    }
    if (permission == "Database Administrator") {
        ui->pushButton4->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton4->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton5->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton5->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton6->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton6->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton7->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton7->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton9->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton9->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton11->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton11->setStyleSheet("background-color: #888888; color: #AAAAAA;");
    }
    if (permission == "Floor Manager") {
        ui->pushButton4->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton4->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton5->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton5->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton6->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton6->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton7->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton7->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton9->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton9->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton10->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton10->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton11->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton11->setStyleSheet("background-color: #888888; color: #AAAAAA;");
    }
    if (permission == "Building Manager") {
        ui->pushButton4->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton4->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton5->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton5->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton6->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton6->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton7->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton7->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton9->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton9->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton10->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton10->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton11->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton11->setStyleSheet("background-color: #888888; color: #AAAAAA;");
    }

    if (permission == "System Administrator") {
        ui->pushButton->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton4->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton4->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton5->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton5->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton6->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton6->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton7->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton7->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton11->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton11->setStyleSheet("background-color: #888888; color: #AAAAAA;");
    }

    if (permission == "Auditor") {
        ui->pushButton->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton4->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton4->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton5->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton5->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton6->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton6->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton7->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton7->setStyleSheet("background-color: #888888; color: #AAAAAA;");
        ui->pushButton10->setEnabled(false); // Botón para modificar base de datos
        ui->pushButton10->setStyleSheet("background-color: #888888; color: #AAAAAA;");
    }
}

menuwindow::~menuwindow()
{
    delete ui;
}

void menuwindow::on_pushButton_clicked()
{
    viewdatabasewindow *databaseWindow = new viewdatabasewindow(this, this->userHandler, *this, clientNode);  // Crear la nueva ventana
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
    createuser *createUser = new createuser(this, this->userHandler, *this, clientNode);  // Crear la nueva ventana
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
    RemoveUser *removeuser = new RemoveUser(this, this->userHandler, *this);  // Crear la nueva ventana
    removeuser->show();  // Mostrar la nueva ventana
    hide();
}


void menuwindow::on_pushButton5_clicked()
{
    ModifyUser *modifyUser = new ModifyUser(this, this->userHandler, *this, this->clientNode);  // Crear la nueva ventana
    modifyUser->show();  // Mostrar la nueva ventana
    hide();
}

void menuwindow::on_pushButton3_clicked()
{
    SensorFloor *sensorFloor = new SensorFloor(this, this->userHandler, *this); // Crear la nueva ventana
    sensorFloor->show();                              // Mostrar la nueva ventana
    hide();
}

void menuwindow::on_pushButton4_clicked()
{
    ViewUser *viewUser = new ViewUser(this, this->userHandler,*this, this->clientNode); // Crear la nueva ventana
    viewUser->show();                        // Mostrar la nueva ventana
    hide();
}

void menuwindow::on_pushButton8_clicked()
{
    sensorBuilding *building = new sensorBuilding(this, this->userHandler, *this); // Crear la nueva ventana
    building->show();                                    // Mostrar la nueva ventana
    hide();
}

void menuwindow::on_pushButton9_clicked()
{
    ViewNode *viewNode = new ViewNode(this, this->userHandler, *this); // Crear la nueva ventana
    viewNode->show();                        // Mostrar la nueva ventana
    hide();
}

void menuwindow::on_pushButton10_clicked()
{
    ViewBackup *viewBackup = new ViewBackup(this, this->userHandler, *this); // Crear la nueva ventana
    viewBackup->show();                            // Mostrar la nueva ventana
    hide();
}

void menuwindow::on_pushButton11_clicked()
{
    viewLog *log = new viewLog(this, this->userHandler, *this, clientNode); // Crear la nueva ventana
    log->show();                      // Mostrar la nueva ventana
    hide();
}

// Eitir una señal al cerrar la ventana
void menuwindow::closeEvent(QCloseEvent *event)
{
    // llamar a la implementación base del manejo del evento
    QMainWindow::closeEvent(event);
    
    // Cerrar la aplicación
    // TODO: verificar que esto permita que se liberen correctamente los recursos. 
    QApplication::quit();
}

void menuwindow::on_pushButton_2_clicked()
{
    mainwindow.show();
    this->hide();
}

