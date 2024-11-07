#include "modifyuser.h"
#include "ui_modifyuser.h"
#include "menuwindow.h"

ModifyUser::ModifyUser(QWidget *parent, UserHandler& userHandler, menuwindow& menu, ClientNode& clientNode)
    : QMainWindow(parent)
    , ui(new Ui::ModifyUser), userHandler(userHandler), menu(menu), clientNode(clientNode)
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
    QString path2 = ":/resource/img/group.png";
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

    // Cargar usuarios
    loadUserList();

    // Conectar la selección de usuario en QListWidget
    connect(ui->listWidget, &QListWidget::itemClicked, this, &ModifyUser::on_listWidget_itemClicked);
}

void ModifyUser::loadUserList() {
    std::vector<std::string> list;
    bool error = clientNode.getUserList(this->clientNode.username, list);
    if(error){
        for(int i = 0; i < list.size(); ++i){
            ui->listWidget->addItem(QString::fromStdString(list[i]));
        }
    } else {
        // TODO: Error.
    }

    QStringList opciones = {"User Administrator", "Database Administrator", "Floor Manager", "Building Manager", "System Administrator", "Auditor"};
    ui->comboBox->addItems(opciones);
}

ModifyUser::~ModifyUser()
{
    delete ui;
}

void ModifyUser::on_pushButton1_clicked()
{
    // Modifica.
    std::string modify_by_user = this->clientNode.username;

    // Recoger datos del formulario
    // selectedUsername;
    QString username = ui->user->text();
    QString password = ui->password->text();
    QString name = ui->nombre_3->text();
    QString lastName = ui->apellido->text();

    // Rol seleccionado y conversión a permisos
    uint8_t permissions = 0;
    QString selectedRole = ui->comboBox->currentText();
    if (selectedRole == "User Administrator") permissions |= USER_ADMINISTRATOR;
    if (selectedRole == "Database Administrator") permissions |= DATABASE_ADMINISTRATOR;
    if (selectedRole == "Floor Manager") permissions |= FLOOR_MANAGER;
    if (selectedRole == "Building Manager") permissions |= BUILDING_MANAGER;
    if (selectedRole == "System Administrator") permissions |= SYSTEM_ADMINISTRATOR;
    if (selectedRole == "Auditor") permissions |= AUDITOR;

    // Variable de respuesta
    std::string response;

    int8_t floors[32] = {0}; // TODO: pisos.

    // Llamada a la función modifyUser
    bool success = clientNode.modifyUser(modify_by_user, selectedUsername,
                                          username.toStdString(), password.toStdString(),
                                          permissions, floors, name.toStdString(),
                                          lastName.toStdString(), response);

}


void ModifyUser::on_pushButton1_2_clicked()
{
    this->menu.show();
    this->hide();
    this->deleteLater();
}

std::string ModifyUser::checkPermissions(uint8_t user_permissions) {
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


void ModifyUser::on_listWidget_itemClicked(QListWidgetItem *item)
{
    // Llama a getUserInformation() con el username seleccionado
    std::string username = item->text().toStdString();
    selectedUsername = username;
    std::vector<std::string> userInfo;
    bool error = clientNode.getUserInformation(this->clientNode.username, username, userInfo);

    //if (userInfo.size() == 4) {
    // Actualiza los QLabel con los datos del usuario seleccionado
    ui->user->setText(QString::fromStdString(userInfo[0]));
    ui->nombre_3->setText(QString::fromStdString(userInfo[1]));
    ui->apellido->setText(QString::fromStdString(userInfo[2]));
    ui->comboBox->setCurrentText(QString::fromStdString(checkPermissions(std::stoi(userInfo[3]))));
}

