#include "removeuser.h"
#include "ui_removeuser.h"

<<<<<<< HEAD
RemoveUser::RemoveUser(QWidget *parent, UserNode& userHandler, menuwindow& menu, ClientNode& clientNode)
=======
RemoveUser::RemoveUser(QWidget *parent, UserNode& userHandler, menuwindow& menu)
>>>>>>> refs/remotes/origin/main
    : QMainWindow(parent)
    , ui(new Ui::RemoveUser), userHandler(userHandler), menu(menu), clientNode(clientNode)
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
    QString path2 = ":/resource/img/remove-user.png";
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

    //
    // Cargar usuarios
    loadUserList();

    // Conectar la selección de usuario en QListWidget
    connect(ui->listWidget, &QListWidget::itemClicked, this, &RemoveUser::on_listWidget_itemClicked);
}

void RemoveUser::loadUserList() {
    std::vector<std::string> list;
    bool error = clientNode.getUserList(this->clientNode.username, list);
    if(error){
        for(int i = 0; i < list.size(); ++i){
            ui->listWidget->addItem(QString::fromStdString(list[i]));
        }
    }
}

RemoveUser::~RemoveUser()
{
    delete ui;
}

void RemoveUser::on_pushButton1_2_clicked()
{
    this->menu.show();
    this->hide();
    this->deleteLater();
}


void RemoveUser::on_listWidget_itemClicked(QListWidgetItem *item)
{
    selectedUser = item->text();
}


void RemoveUser::on_pushButton1_clicked()
{
    std::string username = selectedUser.toStdString();
    std::vector<std::string> userInfo;
    bool error = clientNode.getUserInformation(this->clientNode.username, username, userInfo);
    std::string isActive = userInfo[4];
    bool active;
    if(isActive == "Active"){
        active = true;
    } else {
        active = false;
    }
    std::string response;

    std::cout << "Is active: " << isActive;

    // Delete.
    clientNode.activeDeactivateUser(this->clientNode.username, username, active, response);

    this->menu.show();
    this->hide();
    this->deleteLater();
}

