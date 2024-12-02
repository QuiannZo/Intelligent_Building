#include "viewnode.h"
#include "ui_viewnode.h"

<<<<<<< HEAD
ViewNode::ViewNode(QWidget *parent, UserNode& userHandler, menuwindow& menu, ClientNode& clientNode)
    : QMainWindow(parent), ui(new Ui::ViewNode), userHandler(userHandler), menu(menu), clientNode(clientNode)
=======
ViewNode::ViewNode(QWidget *parent, UserNode& userHandler, menuwindow& menu)
    : QMainWindow(parent), ui(new Ui::ViewNode), userHandler(userHandler), menu(menu)
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

ViewNode::~ViewNode()
{
    delete ui;
}

void ViewNode::on_pushButton1_2_clicked()
{
    this->menu.show();
    this->hide();
    this->deleteLater();
}


void ViewNode::on_backupbtn_clicked()
{
    std::string response;
    response = clientNode.getSystemState();
    ui->textEdit->setText(QString::fromStdString(response));
}

