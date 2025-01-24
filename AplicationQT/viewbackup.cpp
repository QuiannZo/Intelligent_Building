#include "viewbackup.h"
#include "ui_viewbackup.h"

ViewBackup::ViewBackup(QWidget *parent, UserNode& userHandler, menuwindow& menu, ClientNode& clientNode)
<<<<<<< HEAD
    : QMainWindow(parent), ui(new Ui::ViewBackup), clientNode(clientNode),
    userHandler(userHandler), menu(menu)
=======
    : QMainWindow(parent), ui(new Ui::ViewBackup),
    userHandler(userHandler), menu(menu), clientNode(clientNode)
>>>>>>> refs/remotes/origin/main
{
    ui->setupUi(this);

    // Load background
    QPalette palette;
    QPixmap bkgnd(":/resource/img/img1.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    palette.setBrush(QPalette::Window, bkgnd);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

ViewBackup::~ViewBackup()
{
    delete ui;
}

void ViewBackup::on_pushButton1_2_clicked()
{
    this->menu.show();
    this->hide();
    this->deleteLater();
}


void ViewBackup::on_backupbtn_clicked()
{
    std::string response;
<<<<<<< HEAD
    clientNode.getBackupState(this->clientNode.username, response);
=======
    clientNode.getNodeLog(this->clientNode.username, response, 4);
>>>>>>> refs/remotes/origin/main
    ui->textEdit->setText(QString::fromStdString(response));
}

