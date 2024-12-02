#ifndef CREATEUSER_H
#define CREATEUSER_H

#include <QMainWindow>
#include <QDialog>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>
#include "../etapa4/etapa4PI/UserNode.hpp"
<<<<<<< HEAD
#include "../etapa4/etapa4PI/ClientNode.hpp"
=======
>>>>>>> refs/remotes/origin/main
#include "menuwindow.h"
#include "floorselectiondialog.h"

namespace Ui {
class createuser;
}

class createuser : public QMainWindow
{
    Q_OBJECT

public:
    explicit createuser(QWidget *parent, UserNode& userHandler, menuwindow& menu, ClientNode& clientNode);
    ~createuser();
protected:
    void closeEvent(QCloseEvent *event) override;  // Sobrescribir closeEvent
private:
    Ui::createuser *ui;
    UserNode& userHandler;
    menuwindow& menu;
    ClientNode& clientNode;
private slots:
    void onSubmitClicked();
    void on_pushButton1_2_clicked();
};

#endif // CREATEUSER_H
