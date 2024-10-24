#ifndef CREATEUSER_H
#define CREATEUSER_H

#include <QMainWindow>
#include "../UserHandler.hpp"

namespace Ui {
class createuser;
}

class createuser : public QMainWindow
{
    Q_OBJECT

public:
    explicit createuser(QWidget *parent, UserHandler& userHandler);
    ~createuser();
protected:
    void closeEvent(QCloseEvent *event) override;  // Sobrescribir closeEvent
private:
    Ui::createuser *ui;
    UserHandler& userHandler;
private slots:
    void onSubmitClicked();
};

#endif // CREATEUSER_H
