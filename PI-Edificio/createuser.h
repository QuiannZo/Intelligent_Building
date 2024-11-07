#ifndef CREATEUSER_H
#define CREATEUSER_H

#include <QMainWindow>
#include <QDialog>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>
#include "../UserHandler.hpp"
#include "menuwindow.h"
#include "floorselectiondialog.h"

namespace Ui {
class createuser;
}

class createuser : public QMainWindow
{
    Q_OBJECT

public:
    explicit createuser(QWidget *parent, UserHandler& userHandler, menuwindow& menu);
    ~createuser();
protected:
    void closeEvent(QCloseEvent *event) override;  // Sobrescribir closeEvent
private:
    Ui::createuser *ui;
    UserHandler& userHandler;
    menuwindow& menu;
private slots:
    void onSubmitClicked();
    void on_pushButton1_2_clicked();
};

#endif // CREATEUSER_H
