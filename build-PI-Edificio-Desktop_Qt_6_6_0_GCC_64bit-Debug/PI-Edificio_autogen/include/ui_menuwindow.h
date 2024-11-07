/********************************************************************************
** Form generated from reading UI file 'menuwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWINDOW_H
#define UI_MENUWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menuwindow
{
public:
    QWidget *centralwidget;
    QWidget *menuwidget;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QWidget *mainwidget;
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *pushButton2;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *pushButton7;
    QPushButton *pushButton4;
    QPushButton *pushButton5;
    QPushButton *pushButton6;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QPushButton *pushButton11;
    QPushButton *pushButton9;
    QPushButton *pushButton10;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *menuwindow)
    {
        if (menuwindow->objectName().isEmpty())
            menuwindow->setObjectName("menuwindow");
        menuwindow->resize(1000, 600);
        centralwidget = new QWidget(menuwindow);
        centralwidget->setObjectName("centralwidget");
        menuwidget = new QWidget(centralwidget);
        menuwidget->setObjectName("menuwidget");
        menuwidget->setGeometry(QRect(0, 0, 1000, 40));
        label_2 = new QLabel(menuwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 10, 101, 20));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: white;"));
        pushButton_2 = new QPushButton(menuwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(930, 5, 61, 31));
        mainwidget = new QWidget(centralwidget);
        mainwidget->setObjectName("mainwidget");
        mainwidget->setGeometry(QRect(-2, 39, 1011, 560));
        pushButton = new QPushButton(mainwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(170, 60, 191, 131));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        label = new QLabel(mainwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(190, 160, 151, 20));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("color: white;"));
        pushButton2 = new QPushButton(mainwidget);
        pushButton2->setObjectName("pushButton2");
        pushButton2->setGeometry(QRect(400, 60, 191, 131));
        pushButton2->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        label_3 = new QLabel(mainwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(450, 160, 101, 20));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("color: white;"));
        label_6 = new QLabel(mainwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(680, 160, 101, 20));
        label_6->setFont(font1);
        label_6->setStyleSheet(QString::fromUtf8("color: white;"));
        label_7 = new QLabel(mainwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(460, 320, 91, 20));
        label_7->setFont(font1);
        label_7->setStyleSheet(QString::fromUtf8("color: white;"));
        label_8 = new QLabel(mainwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(700, 320, 71, 20));
        label_8->setFont(font1);
        label_8->setStyleSheet(QString::fromUtf8("color: white;"));
        label_9 = new QLabel(mainwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(230, 320, 91, 20));
        label_9->setFont(font1);
        label_9->setStyleSheet(QString::fromUtf8("color: white;"));
        pushButton7 = new QPushButton(mainwidget);
        pushButton7->setObjectName("pushButton7");
        pushButton7->setGeometry(QRect(630, 60, 191, 131));
        pushButton7->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        pushButton4 = new QPushButton(mainwidget);
        pushButton4->setObjectName("pushButton4");
        pushButton4->setGeometry(QRect(170, 220, 191, 131));
        pushButton4->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        pushButton5 = new QPushButton(mainwidget);
        pushButton5->setObjectName("pushButton5");
        pushButton5->setGeometry(QRect(400, 220, 191, 131));
        pushButton5->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        pushButton6 = new QPushButton(mainwidget);
        pushButton6->setObjectName("pushButton6");
        pushButton6->setGeometry(QRect(630, 220, 191, 131));
        pushButton6->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        label_10 = new QLabel(mainwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(690, 480, 101, 20));
        label_10->setFont(font1);
        label_10->setStyleSheet(QString::fromUtf8("color: white;"));
        label_11 = new QLabel(mainwidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(190, 480, 161, 20));
        label_11->setFont(font1);
        label_11->setStyleSheet(QString::fromUtf8("color: white;"));
        label_12 = new QLabel(mainwidget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(440, 480, 121, 20));
        label_12->setFont(font1);
        label_12->setStyleSheet(QString::fromUtf8("color: white;"));
        pushButton11 = new QPushButton(mainwidget);
        pushButton11->setObjectName("pushButton11");
        pushButton11->setGeometry(QRect(630, 380, 191, 131));
        pushButton11->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        pushButton9 = new QPushButton(mainwidget);
        pushButton9->setObjectName("pushButton9");
        pushButton9->setGeometry(QRect(170, 380, 191, 131));
        pushButton9->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        pushButton10 = new QPushButton(mainwidget);
        pushButton10->setObjectName("pushButton10");
        pushButton10->setGeometry(QRect(400, 380, 191, 131));
        pushButton10->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        pushButton10->raise();
        label_12->raise();
        pushButton9->raise();
        pushButton11->raise();
        label_10->raise();
        label_11->raise();
        pushButton7->raise();
        pushButton6->raise();
        pushButton5->raise();
        pushButton4->raise();
        pushButton->raise();
        label->raise();
        pushButton2->raise();
        label_3->raise();
        label_6->raise();
        label_7->raise();
        label_8->raise();
        label_9->raise();
        menuwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(menuwindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        menuwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(menuwindow);
        statusbar->setObjectName("statusbar");
        menuwindow->setStatusBar(statusbar);

        retranslateUi(menuwindow);

        QMetaObject::connectSlotsByName(menuwindow);
    } // setupUi

    void retranslateUi(QMainWindow *menuwindow)
    {
        menuwindow->setWindowTitle(QCoreApplication::translate("menuwindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("menuwindow", "Menu", nullptr));
        pushButton_2->setText(QCoreApplication::translate("menuwindow", "Log out", nullptr));
        pushButton->setText(QString());
        label->setText(QCoreApplication::translate("menuwindow", "View Sensor Database", nullptr));
        pushButton2->setText(QString());
        label_3->setText(QCoreApplication::translate("menuwindow", "Edit Database", nullptr));
        label_6->setText(QCoreApplication::translate("menuwindow", "Deactivate user", nullptr));
        label_7->setText(QCoreApplication::translate("menuwindow", "Modify User", nullptr));
        label_8->setText(QCoreApplication::translate("menuwindow", "Add User", nullptr));
        label_9->setText(QCoreApplication::translate("menuwindow", "View User", nullptr));
        pushButton7->setText(QString());
        pushButton4->setText(QString());
        pushButton5->setText(QString());
        pushButton6->setText(QString());
        label_10->setText(QCoreApplication::translate("menuwindow", "View Logs", nullptr));
        label_11->setText(QCoreApplication::translate("menuwindow", "View Node Information", nullptr));
        label_12->setText(QCoreApplication::translate("menuwindow", "View Backup State", nullptr));
        pushButton11->setText(QString());
        pushButton9->setText(QString());
        pushButton10->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class menuwindow: public Ui_menuwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUWINDOW_H
