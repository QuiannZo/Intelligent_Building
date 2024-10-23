#include "mainwindow.h"
#include "menuwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent, UserHandler &userHandler)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    userHandler(userHandler)
{
    ui->setupUi(this);

    //Fondos para los widgets y mainw.
    // Load background.
    QPalette palette;
    QPixmap bkgnd(":/resource/img/mainw.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    palette.setBrush(QPalette::Window, bkgnd);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
    // delete userHandler;
}

void MainWindow::on_pushButton1_clicked()
{
    // Obtener username y la contraseña
    QString username = ui->lineEdit_2->text();
    QString password = ui->lineEdit->text();

    // Generar el hash de la contraseña usando UserHandler
    std::string usernameStr = username.toStdString();
    std::string passwordStr = password.toStdString();

    // Genera el hash de la contraseña
    std::string passwordHash = userHandler.generateHash(passwordStr);
    std::string error;

    //userHandler.addUser("superUser", "username01", userHandler.generateHash("password01")
      //                  , USER_ADMINISTRATOR, "", "name01", "lastName01", "00000001");

    // Mostrar el hash de la contraseña en un cuadro de mensaje
    QMessageBox::information(this, "user", QString::fromStdString(usernameStr));
    QMessageBox::information(this, "Password Hash", QString::fromStdString(passwordHash));

    // Autenticación
    if (userHandler.authenticateUser(usernameStr, passwordHash, error)) {
        menuwindow *menuWindow = new menuwindow(this, this->userHandler);
        menuWindow->show();
        hide();
    } else {
        // mensaje de error
        QMessageBox::warning(this, "Incorrect user.", QString::fromStdString(error));
    }

    QMessageBox::information(this, "error", QString::fromStdString(error));
}
