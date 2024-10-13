#ifndef VIEWDATABASEWINDOW_H
#define VIEWDATABASEWINDOW_H

#include <QMainWindow>
#include <QFile>

namespace Ui {
class viewdatabasewindow;
}

class viewdatabasewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewdatabasewindow(QWidget *parent = nullptr);
    ~viewdatabasewindow();

private:
    Ui::viewdatabasewindow *ui;
};

#endif // VIEWDATABASEWINDOW_H
