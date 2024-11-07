#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "menuwindow.h"
#include <QMessageBox>
#include <vector>

MainWindow::MainWindow(QWidget *parent, UserHandler &userHandler, ClientNode& clientNode)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    userHandler(userHandler),
    clientNode(clientNode)
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
    //std::string passwordHash = userHandler.generateHash(passwordStr);
    std::vector<std::string> result;
    //std::string error;

    // Autenticación
    if (clientNode.authenticateUser(usernameStr, passwordStr, result)) {
        // crear la ventana de menu
        menuwindow* menu = new menuwindow(this, this->userHandler, *this, this->clientNode);
        menu->show();
        this->hide();

        // guardar los datos.
        clientNode.name = result[0];
        clientNode.lastName = result[1];
        clientNode.permissions = std::stoi(result[2]);
        clientNode.username = usernameStr;
    } else {
        // mensaje de error
        QMessageBox::warning(this, "Incorrect user.", QString::fromStdString(result[0]));
    }
}
