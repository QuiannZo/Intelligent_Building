#include "viewbackup.h"
#include "ui_viewbackup.h"

ViewBackup::ViewBackup(QWidget *parent, UserHandler& userHandler, menuwindow& menu)
    : QMainWindow(parent), ui(new Ui::ViewBackup),
    userHandler(userHandler), menu(menu)
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

