#include "viewlog.h"
#include "ui_viewlog.h"

viewLog::viewLog(QWidget *parent, UserNode& userHandler, menuwindow& menu, ClientNode& clientNode)
    : QMainWindow(parent)
    , ui(new Ui::viewLog), userHandler(userHandler), menu(menu), clientNode(clientNode)
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

}

viewLog::~viewLog()
{
    delete ui;
}

void viewLog::on_pushButton1_2_clicked()
{
    this->menu.show();
    this->hide();
    this->deleteLater();
}


void viewLog::on_datanodebtn_clicked()
{
    std::string response;
    clientNode.getNodeLog(this->clientNode.username, response, 4);
    ui->textEdit->setText(QString::fromStdString(response));
}

void viewLog::on_interlogbtn_clicked()
{
    std::string response;
    clientNode.getNodeLog(this->clientNode.username, response, 2);
    ui->textEdit->setText(QString::fromStdString(response));
}


void viewLog::on_userlogbtn_clicked()
{
    std::string response;
    clientNode.getNodeLog(this->clientNode.username, response, 3);
    ui->textEdit->setText(QString::fromStdString(response));
}

