#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>

namespace Ui {
class menuwindow;
}

class menuwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit menuwindow(QWidget *parent = nullptr);
    ~menuwindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton4_clicked();

private:
    Ui::menuwindow *ui;
};

#endif // MENUWINDOW_H
