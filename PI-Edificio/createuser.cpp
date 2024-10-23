#include "createuser.h"
#include "ui_createuser.h"

createuser::createuser(QWidget *parent, UserHandler& userHandler)
    : QMainWindow(parent)
    , ui(new Ui::createuser), userHandler(userHandler)
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
    ui->username->setStyleSheet("QLabel { "
                              "color: #FFFFFF; }");

    // contraseña label
    ui->password->setStyleSheet("QLabel { "
                              "color: #FFFFFF; }");

    // name label
    ui->name->setStyleSheet("QLabel { "
                              "color: #FFFFFF; }");
    // name label
    ui->lastName->setStyleSheet("QLabel { "
                            "color: #FFFFFF; }");
    // Roles
    ui->role->setStyleSheet("QLabel { "
                            "color: #FFFFFF; }");
    ui->dbAdm->setStyleSheet("QRadioButton {"
                             "   color: white;"
                             "}"
                             "QRadioButton::indicator:checked {"
                             "   background-color: black;"
                             "}");
    ui->floorMng->setStyleSheet("QRadioButton {"
                                "   color: white;"
                                "}"
                                "QRadioButton::indicator:checked {"
                                "   background-color: black;"
                                "}");
    ui->Auditor->setStyleSheet("QRadioButton {"
                                "   color: white;"
                                "}"
                                "QRadioButton::indicator:checked {"
                                "   background-color: black;"
                                "}"
                                );
    ui->systemAd->setStyleSheet("QRadioButton {"
                               "   color: white;"
                               "}"
                               "QRadioButton::indicator:checked {"
                               "   background-color: black;"
                               "}"
                               );
    ui->userAd->setStyleSheet("QRadioButton {"
                                "   color: white;"
                                "}"
                                "QRadioButton::indicator:checked {"
                                "   background-color: black;"
                                "}"
                                );
    ui->buildingMng->setStyleSheet("QRadioButton {"
                              "   color: white;"
                              "}"
                              "QRadioButton::indicator:checked {"
                              "   background-color: black;"
                              "}"
                              );
    connect(ui->createUser, &QPushButton::clicked, this, &createuser::onSubmitClicked);
}

createuser::~createuser()
{
    delete ui;
}

void createuser::onSubmitClicked()
{
    // Obtener datos de los campos
    QString username = ui->usernamelineEdit->text();
    QString password = ui->passwordlineEdit->text();
    QString name = ui->namelineEdit->text();
    QString lastName = ui->lastNamelineEdit->text();
    QString role;  // Variable para almacenar el rol seleccionado
    if (ui->dbAdm->isChecked()) {
        role = "Database Administrator";
    } else if (ui->floorMng->isChecked()) {
        role = "Floor Manager";
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
    std::string hash = this->userHandler.generateHash(password.toStdString());
    if(this->userHandler.addUser("superuser", username.toStdString(), hash, 1, "[]", name.toStdString(), lastName.toStdString(), "ID00000")) {
        //this->userHandler->saveUsersFile();
        qDebug() << "User added";
    }

    // por el momento vamos a imprimir aquí
    qDebug() << "Username:" << username;
    qDebug() << "Password:" << password;
    qDebug() << "Name:" << name;
    qDebug() << "Last Name:" << lastName;
    qDebug() << "Role:" << role;
}

