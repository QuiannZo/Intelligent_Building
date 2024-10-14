#ifndef VIEWBACKUP_H
#define VIEWBACKUP_H

#include <QMainWindow>

namespace Ui {
class ViewBackup;
}

class ViewBackup : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewBackup(QWidget *parent = nullptr);
    ~ViewBackup();

private:
    Ui::ViewBackup *ui;
};

#endif // VIEWBACKUP_H
