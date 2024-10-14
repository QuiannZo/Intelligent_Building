#include "viewbackup.h"
#include "ui_viewbackup.h"

ViewBackup::ViewBackup(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ViewBackup)
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

ViewBackup::~ViewBackup()
{
    delete ui;
}
