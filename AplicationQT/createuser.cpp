#include <qstring.h>
#include "createuser.h"
#include "ui_createuser.h"
#include "menuwindow.h"

createuser::createuser(QWidget *parent, UserNode& userHandler, menuwindow& menu, ClientNode& clientNode)
    : QMainWindow(parent)
    , ui(new Ui::createuser), userHandler(userHandler), menu(menu), clientNode(clientNode)
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
    // Labels
    // nombre label
    QString labelStyle = "QLabel { ""color: #FFFFFF; }";
    ui->username->setStyleSheet(labelStyle);
    // contraseña label
    ui->password->setStyleSheet(labelStyle);
    // name label
    ui->name->setStyleSheet(labelStyle);
    // name label
    ui->lastName->setStyleSheet(labelStyle);
    // Roles
    ui->role->setStyleSheet(labelStyle);
    // Radio Buttons:
    QString radioButtonStyle = "QRadioButton {""   color: white;""}"
                               "QRadioButton::indicator:checked {"
                               "   background-color: black;""}";
    ui->dbAdm->setStyleSheet(radioButtonStyle);
    ui->floorMng->setStyleSheet(radioButtonStyle);
    ui->Auditor->setStyleSheet(radioButtonStyle);
    ui->systemAd->setStyleSheet(radioButtonStyle);
    ui->userAd->setStyleSheet(radioButtonStyle);
    ui->buildingMng->setStyleSheet(radioButtonStyle);
    connect(ui->createUser, &QPushButton::clicked, this, &createuser::onSubmitClicked);
}

createuser::~createuser()
{
    delete ui;
}

void createuser::closeEvent(QCloseEvent *event)
{
      // Llamar a la implementación base del manejo del evento
    QMainWindow::closeEvent(event);
    // Cerrar la aplicación
    QApplication::quit();  
}

void createuser::onSubmitClicked()
{
    QString username = ui->usernamelineEdit->text();
    QString password = ui->passwordlineEdit->text();
    QString name = ui->namelineEdit->text();
    QString lastName = ui->lastNamelineEdit->text();
    QString role;
    int8_t floors[32] = {}; // Inicializa los pisos seleccionados como vacío.

    if (ui->dbAdm->isChecked()) {
        role = "Database Administrator";
    } else if (ui->floorMng->isChecked()) {
        role = "Floor Manager";

        // Crear y mostrar el diálogo de selección de pisos
        FloorSelectionDialog floorDialog(this);
        if (floorDialog.exec() == QDialog::Accepted) {
            floorDialog.getSelectedFloors(floors, 32); // Almacena los pisos seleccionados en el arreglo
        }
    } else if (ui->Auditor->isChecked()) {
        role = "Auditor";
    } else if (ui->systemAd->isChecked()) {
        role = "System Administrator";
    } else if (ui->userAd->isChecked()) {
        role = "User Administrator";
    } else if (ui->buildingMng->isChecked()) {
        role = "Building Manager";
    } else {
        role = "Invalid";
    }

    std::string response;
    if(this->clientNode.addUser(this->clientNode.username, username.toStdString(), password.toStdString(), 1, floors, name.toStdString(), lastName.toStdString(), response)){
        qDebug() << "User added correctly.";
    }

    qDebug() << "Username:" << username;
    qDebug() << "Password:" << password;
    qDebug() << "Name:" << name;
    qDebug() << "Last Name:" << lastName;
    qDebug() << "Role:" << role;
    qDebug() << "Floors:" << floors;

    this->menu.show();
    this->hide();
    this->deleteLater();
}


void createuser::on_pushButton1_2_clicked()
{
    this->menu.show();
    this->hide();
    this->deleteLater();
}

