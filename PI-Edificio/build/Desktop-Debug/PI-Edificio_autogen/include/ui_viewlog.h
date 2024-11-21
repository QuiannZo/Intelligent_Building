/********************************************************************************
** Form generated from reading UI file 'viewlog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWLOG_H
#define UI_VIEWLOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_viewLog
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton1_2;
    QLabel *label_15;
    QPushButton *interlogbtn;
    QPushButton *userlogbtn;
    QLabel *label_13;
    QPushButton *datanodebtn;
    QLabel *label_14;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *viewLog)
    {
        if (viewLog->objectName().isEmpty())
            viewLog->setObjectName("viewLog");
        viewLog->resize(1000, 600);
        centralwidget = new QWidget(viewLog);
        centralwidget->setObjectName("centralwidget");
        pushButton1_2 = new QPushButton(centralwidget);
        pushButton1_2->setObjectName("pushButton1_2");
        pushButton1_2->setGeometry(QRect(20, 10, 141, 26));
        QFont font;
        font.setBold(true);
        pushButton1_2->setFont(font);
        pushButton1_2->setStyleSheet(QString::fromUtf8("    QPushButton {\n"
"        background-color: white;\n"
"        color: #007ACC; /* Text color */\n"
"        border-radius: 25px; /* Rounded corners */\n"
"        font-weight: bold;\n"
"        font-size: 16px;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #E0E0E0; /* Hover effect */\n"
"        box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.2);\n"
"    }\n"
"    QPushButton:pressed {\n"
"        background-color: #B0B0B0; /* Click effect */\n"
"    }"));
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(110, 270, 101, 20));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        label_15->setFont(font1);
        label_15->setStyleSheet(QString::fromUtf8("color: white;"));
        interlogbtn = new QPushButton(centralwidget);
        interlogbtn->setObjectName("interlogbtn");
        interlogbtn->setGeometry(QRect(60, 170, 191, 51));
        interlogbtn->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        userlogbtn = new QPushButton(centralwidget);
        userlogbtn->setObjectName("userlogbtn");
        userlogbtn->setGeometry(QRect(60, 250, 191, 51));
        userlogbtn->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(110, 110, 111, 20));
        label_13->setFont(font1);
        label_13->setStyleSheet(QString::fromUtf8("color: white;"));
        datanodebtn = new QPushButton(centralwidget);
        datanodebtn->setObjectName("datanodebtn");
        datanodebtn->setGeometry(QRect(60, 90, 191, 51));
        datanodebtn->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(100, 190, 121, 20));
        label_14->setFont(font1);
        label_14->setStyleSheet(QString::fromUtf8("color: white;"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(310, 90, 631, 461));
        viewLog->setCentralWidget(centralwidget);
        userlogbtn->raise();
        datanodebtn->raise();
        pushButton1_2->raise();
        label_15->raise();
        interlogbtn->raise();
        label_13->raise();
        label_14->raise();
        textEdit->raise();
        menubar = new QMenuBar(viewLog);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        viewLog->setMenuBar(menubar);
        statusbar = new QStatusBar(viewLog);
        statusbar->setObjectName("statusbar");
        viewLog->setStatusBar(statusbar);

        retranslateUi(viewLog);

        QMetaObject::connectSlotsByName(viewLog);
    } // setupUi

    void retranslateUi(QMainWindow *viewLog)
    {
        viewLog->setWindowTitle(QCoreApplication::translate("viewLog", "MainWindow", nullptr));
        pushButton1_2->setText(QCoreApplication::translate("viewLog", "Return", nullptr));
        label_15->setText(QCoreApplication::translate("viewLog", "User Node Log", nullptr));
        interlogbtn->setText(QString());
        userlogbtn->setText(QString());
        label_13->setText(QCoreApplication::translate("viewLog", "Data Node Log", nullptr));
        datanodebtn->setText(QString());
        label_14->setText(QCoreApplication::translate("viewLog", "Intermediary Log", nullptr));
    } // retranslateUi

};

namespace Ui {
    class viewLog: public Ui_viewLog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWLOG_H
