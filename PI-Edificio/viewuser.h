#ifndef VIEWUSER_H
#define VIEWUSER_H

#include <QMainWindow>

namespace Ui {
class ViewUser;
}

class ViewUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewUser(QWidget *parent = nullptr);
    ~ViewUser();

private:
    Ui::ViewUser *ui;
};

#endif // VIEWUSER_H
