#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "menuwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
}

void MainWindow::on_pushButton1_clicked()
{
    menuwindow *menuWindow = new menuwindow(this);  // Crear la nueva ventana
    menuWindow->show();  // Mostrar la nueva ventana
    hide();
}
