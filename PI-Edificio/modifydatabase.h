#ifndef MODIFYDATABASE_H
#define MODIFYDATABASE_H

#include <QMainWindow>

namespace Ui {
class ModifyDataBase;
}

class ModifyDataBase : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModifyDataBase(QWidget *parent = nullptr);
    ~ModifyDataBase();

private:
    Ui::ModifyDataBase *ui;
};

#endif // MODIFYDATABASE_H
