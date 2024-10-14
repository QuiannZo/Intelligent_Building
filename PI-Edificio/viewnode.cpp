#include "viewnode.h"
#include "ui_viewnode.h"

ViewNode::ViewNode(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ViewNode)
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
