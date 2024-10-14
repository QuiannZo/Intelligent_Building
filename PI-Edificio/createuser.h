#ifndef CREATEUSER_H
#define CREATEUSER_H

#include <QMainWindow>

namespace Ui {
class createuser;
}

class createuser : public QMainWindow
{
    Q_OBJECT

public:
    explicit createuser(QWidget *parent = nullptr);
    ~createuser();
private:
    Ui::createuser *ui;
private slots:
    void onSubmitClicked();
};

#endif // CREATEUSER_H
