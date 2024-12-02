#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../etapa4/etapa4PI/UserNode.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, UserNode& userHandler, ClientNode& clientNode);
    ~MainWindow();

private slots:
    void on_pushButton1_clicked();

private:
    Ui::MainWindow *ui;
    // El `userHandler` se va a guardar como referencia
    UserNode& userHandler;
    ClientNode& clientNode;
};
#endif // MAINWINDOW_H
