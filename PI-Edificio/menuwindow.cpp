#include "menuwindow.h"
#include "ui_menuwindow.h"

menuwindow::menuwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menuwindow)
{
    ui->setupUi(this);
}

menuwindow::~menuwindow()
{
    delete ui;
}
