#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "menuwindow.h"
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
    std::cout << "Se ejecutó destructor de MainWindow.\n";
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
    // crear la ventana de menu
    std::string passwordHash = userHandler.generateHash(passwordStr);
    std::string error;

    // Autenticación
    if (userHandler.authenticateUser(usernameStr, passwordHash, error)) {
        // crear la ventana de menu
        menuwindow* menu = new menuwindow(this, this->userHandler, *this);
        menu->show();
        this->hide();
    } else {
        // mensaje de error
        QMessageBox::warning(this, "Incorrect user.", QString::fromStdString(error));
    }
}
