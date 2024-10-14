#ifndef MODIFYUSER_H
#define MODIFYUSER_H

#include <QMainWindow>

namespace Ui {
class ModifyUser;
}

class ModifyUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModifyUser(QWidget *parent = nullptr);
    ~ModifyUser();

private:
    Ui::ModifyUser *ui;
};

#endif // MODIFYUSER_H
