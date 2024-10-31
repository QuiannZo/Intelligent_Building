#include "viewnode.h"
#include "ui_viewnode.h"

ViewNode::ViewNode(QWidget *parent, UserHandler& userHandler, menuwindow& menu)
    : QMainWindow(parent), ui(new Ui::ViewNode), userHandler(userHandler), menu(menu)
{
    ui->setupUi(this);

    // Load background
    QPalette palette;
    QPixmap bkgnd(":/resource/img/build.png");
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

