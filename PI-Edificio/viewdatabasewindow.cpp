#include "viewdatabasewindow.h"
#include "ui_viewdatabasewindow.h"

viewdatabasewindow::viewdatabasewindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::viewdatabasewindow)
{
    ui->setupUi(this);
}

viewdatabasewindow::~viewdatabasewindow()
{
    delete ui;
}
