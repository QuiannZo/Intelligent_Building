#ifndef VIEWNODE_H
#define VIEWNODE_H

#include <QMainWindow>

namespace Ui {
class ViewNode;
}

class ViewNode : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewNode(QWidget *parent = nullptr);
    ~ViewNode();

private:
    Ui::ViewNode *ui;
};

#endif // VIEWNODE_H
