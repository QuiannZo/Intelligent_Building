#include "viewuser.h"
#include "ui_viewuser.h"

ViewUser::ViewUser(QWidget *parent, UserNode& userHandler, menuwindow& menu, ClientNode& clientNode)
    : QMainWindow(parent)
    , ui(new Ui::ViewUser), userHandler(userHandler), menu(menu), clientNode(clientNode)
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
    /*std::string filep = userHandler.getUsersFile();
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
    }*/
    std::vector<std::string> list;
    bool error = clientNode.getUserList(this->clientNode.username, list);
    if(error){
        for(int i = 0; i < list.size(); ++i){
            ui->listWidget->addItem(QString::fromStdString(list[i]));
        }
    } else {
        // TODO: Error.
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

std::string ViewUser::checkPermissions(uint8_t user_permissions) {
    std::vector<std::string> result;

    if (user_permissions & USER_ADMINISTRATOR) {
        result.push_back("User Administrator");
    }
    if (user_permissions & DATABASE_ADMINISTRATOR) {
        result.push_back("Database Administrator");
    }
    if (user_permissions & FLOOR_MANAGER) {
        result.push_back("Floor Manager");
    }
    if (user_permissions & BUILDING_MANAGER) {
        result.push_back("Building Manager");
    }
    if (user_permissions & SYSTEM_ADMINISTRATOR) {
        result.push_back("System Administrator");
    }
    if (user_permissions & AUDITOR) {
        result.push_back("Auditor");
    }

    result.push_back("No permissions assigned.");

    return result[0];
}

void ViewUser::on_listWidget_itemClicked(QListWidgetItem *item)
{
    // Llama a getUserInformation() con el username seleccionado
    std::string username = item->text().toStdString();
    std::vector<std::string> userInfo;
    bool error = clientNode.getUserInformation(this->clientNode.username, username, userInfo);

    //if (userInfo.size() == 4) {
        // Actualiza los QLabel con los datos del usuario seleccionado
        ui->user->setText(QString::fromStdString(userInfo[0]));
        ui->nombre->setText(QString::fromStdString(userInfo[1]));
        ui->apellido->setText(QString::fromStdString(userInfo[2]));
        ui->rol->setText(QString::fromStdString(checkPermissions(std::stoi(userInfo[3]))));
        ui->ultimaActividad->setText(QString::fromStdString(userInfo[4]));
    //} else {
        //qDebug() << "Error: Información incompleta o usuario no encontrado.";
    //}
}
