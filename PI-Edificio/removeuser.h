#ifndef REMOVEUSER_H
#define REMOVEUSER_H

#include <QMainWindow>

namespace Ui {
class RemoveUser;
}

class RemoveUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit RemoveUser(QWidget *parent = nullptr);
    ~RemoveUser();

private:
    Ui::RemoveUser *ui;
};

#endif // REMOVEUSER_H
