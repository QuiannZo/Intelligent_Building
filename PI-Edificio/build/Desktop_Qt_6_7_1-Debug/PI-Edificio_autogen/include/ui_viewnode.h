/********************************************************************************
** Form generated from reading UI file 'viewnode.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWNODE_H
#define UI_VIEWNODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewNode
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ViewNode)
    {
        if (ViewNode->objectName().isEmpty())
            ViewNode->setObjectName("ViewNode");
        ViewNode->resize(1000, 600);
        centralwidget = new QWidget(ViewNode);
        centralwidget->setObjectName("centralwidget");
        ViewNode->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ViewNode);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        ViewNode->setMenuBar(menubar);
        statusbar = new QStatusBar(ViewNode);
        statusbar->setObjectName("statusbar");
        ViewNode->setStatusBar(statusbar);

        retranslateUi(ViewNode);

        QMetaObject::connectSlotsByName(ViewNode);
    } // setupUi

    void retranslateUi(QMainWindow *ViewNode)
    {
        ViewNode->setWindowTitle(QCoreApplication::translate("ViewNode", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewNode: public Ui_ViewNode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWNODE_H
