#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "viewdatabasewindow.h"

menuwindow::menuwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menuwindow)
{
    ui->setupUi(this);

    //Fondos para los widgets y mainw.
    // Load background.
    QString path = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/a1.jpeg";
    QPixmap bkgnd(path);

    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    // menuwidget.
    QString path2 = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/primary.jpeg";
    QPixmap bkgnd2(path2);
    bkgnd2 = bkgnd2.scaled(ui->menuwidget->size(), Qt::IgnoreAspectRatio);

    QPalette palette2;
    palette2.setBrush(QPalette::Window, bkgnd2);
    ui->menuwidget->setAutoFillBackground(true);
    ui->menuwidget->setPalette(palette2);

    // Botones.
    // icono y el texto
    QString path3 = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/database.png";
    ui->pushButton->setIcon(QIcon(path3));  // Ruta del icono
        ui->pushButton->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/database.png";
    ui->pushButton2->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton2->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/sensor.png";
    ui->pushButton3->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton3->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/user.png";
    ui->pushButton4->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton4->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/group.png";
    ui->pushButton5->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton5->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/add-user.png";
    ui->pushButton6->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton6->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/remove-user.png";
    ui->pushButton7->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton7->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/sensor.png";
    ui->pushButton8->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton8->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/document.png";
    ui->pushButton9->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton9->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/database (1).png";
    ui->pushButton10->setIcon(QIcon(path3));  // Ruta del icono
    ui->pushButton10->setIconSize(QSize(48, 48));  // Ajusta el tamaño del icono

    path3 = QCoreApplication::applicationDirPath() + "/../PI-Edificio/img/document.png";
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

