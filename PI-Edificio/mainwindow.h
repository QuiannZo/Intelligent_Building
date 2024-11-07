#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../UserHandler.hpp"
#include "../etapa3PI/ClientNode.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, UserHandler& userHandler, ClientNode& clientNode);
    ~MainWindow();

private slots:
    void on_pushButton1_clicked();

private:
    Ui::MainWindow *ui;
    // El `userHandler` se va a guardar como referencia
    UserHandler& userHandler;
    ClientNode& clientNode;
};
#endif // MAINWINDOW_H
