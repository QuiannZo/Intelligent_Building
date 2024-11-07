#include "viewuser.h"
#include "ui_viewuser.h"

ViewUser::ViewUser(QWidget *parent, UserHandler& userHandler, menuwindow& menu)
    : QMainWindow(parent)
    , ui(new Ui::ViewUser), userHandler(userHandler), menu(menu)
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
    /*QString path2 = ":/resource/img/user.png";
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
    */

    // nombre label
    ui->nombre->setStyleSheet("QLabel { "
                              "background-color: #FFFFFF; "
                              "color: #000000; }");

    // apellido label
    ui->apellido->setStyleSheet("QLabel { "
                                "background-color: #FFFFFF; "
                                "color: #000000; }");

    // rol label
    ui->rol->setStyleSheet("QLabel { "
                           "background-color: #FFFFFF; "
                           "color: #000000; }");

    // ultimaActividad label
    ui->ultimaActividad->setStyleSheet("QLabel { "
                           "background-color: #FFFFFF; "
                           "color: #000000; }");

    // Load users list.

    // Cargar usuarios
    loadUserList();

    // Conectar la selección de usuario en QListWidget
    connect(ui->listWidget, &QListWidget::itemClicked, this, &ViewUser::on_listWidget_itemClicked);

}

void ViewUser::loadUserList() {
    // Abrir el archivo CSV y cargar los usernames en QListWidget
    std::string filep = userHandler.getUsersFile();
    QFile file = (QString::fromStdString(filep));  // Cambia a la ruta de tu archivo
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        in.readLine(); // Ignora la primera línea de cabecera

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList userInfo = line.split(',');
            if (userInfo.size() >= 1) {
                ui->listWidget->addItem(userInfo[0]); // Añade solo el username
            }
        }
        file.close();
    }
}

ViewUser::~ViewUser()
{
    delete ui;
}

void ViewUser::on_pushButton1_2_clicked()
{
    this->menu.show();
    this->hide();
    this->deleteLater();
}


void ViewUser::on_listWidget_itemClicked(QListWidgetItem *item)
{
    // Llama a getUserInformation() con el username seleccionado
    std::string username = item->text().toStdString();
    std::vector<std::string> userInfo = userHandler.getUserInformation(username);

    if (userInfo.size() == 10) {
        // Actualiza los QLabel con los datos del usuario seleccionado
        ui->user->setText(QString::fromStdString(userInfo[0]));
        ui->nombre->setText(QString::fromStdString(userInfo[4]));
        ui->apellido->setText(QString::fromStdString(userInfo[5]));
        ui->ultimaActividad->setText(QString::fromStdString(userInfo[8]));
        //ui->rol->setText(QString::fromStdString(userInfo[9] == "1" ? "Active" : "Inactive"));
    } else {
        qDebug() << "Error: Información incompleta o usuario no encontrado.";
    }
}

