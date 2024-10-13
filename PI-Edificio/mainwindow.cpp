#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "menuwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load background.
    QString path = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/mainw.jpg";
    QPixmap bkgnd(path);
    if (bkgnd.isNull()) {
        qDebug() << "Failed to load image from path:" << path;}

    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
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
