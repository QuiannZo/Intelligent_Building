#ifndef VIEWLOG_H
#define VIEWLOG_H

#include <QMainWindow>

namespace Ui {
class viewLog;
}

class viewLog : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewLog(QWidget *parent = nullptr);
    ~viewLog();

private:
    Ui::viewLog *ui;
};

#endif // VIEWLOG_H
