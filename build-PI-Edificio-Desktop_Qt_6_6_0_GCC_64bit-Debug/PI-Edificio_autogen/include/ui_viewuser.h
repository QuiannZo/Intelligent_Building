/********************************************************************************
** Form generated from reading UI file 'viewuser.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWUSER_H
#define UI_VIEWUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewUser
{
public:
    QWidget *centralwidget;
    QLabel *nombre;
    QLabel *apellido;
    QLabel *rol;
    QLabel *ultimaActividad;
    QPushButton *pushButton1_2;
    QLabel *label;
    QListWidget *listWidget;
    QLabel *label_2;
    QLabel *user;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ViewUser)
    {
        if (ViewUser->objectName().isEmpty())
            ViewUser->setObjectName("ViewUser");
        ViewUser->resize(1000, 600);
        centralwidget = new QWidget(ViewUser);
        centralwidget->setObjectName("centralwidget");
        nombre = new QLabel(centralwidget);
        nombre->setObjectName("nombre");
        nombre->setGeometry(QRect(110, 270, 291, 31));
        QFont font;
        font.setPointSize(16);
        nombre->setFont(font);
        apellido = new QLabel(centralwidget);
        apellido->setObjectName("apellido");
        apellido->setGeometry(QRect(110, 310, 291, 31));
        apellido->setFont(font);
        rol = new QLabel(centralwidget);
        rol->setObjectName("rol");
        rol->setGeometry(QRect(110, 350, 291, 31));
        rol->setFont(font);
        ultimaActividad = new QLabel(centralwidget);
        ultimaActividad->setObjectName("ultimaActividad");
        ultimaActividad->setGeometry(QRect(110, 390, 291, 31));
        ultimaActividad->setFont(font);
        pushButton1_2 = new QPushButton(centralwidget);
        pushButton1_2->setObjectName("pushButton1_2");
        pushButton1_2->setGeometry(QRect(20, 10, 141, 26));
        QFont font1;
        font1.setBold(true);
        pushButton1_2->setFont(font1);
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
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(390, 30, 181, 31));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        label->setPalette(palette);
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        label->setFont(font2);
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(670, 150, 271, 381));
        listWidget->setFont(font2);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(750, 110, 121, 31));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        label_2->setPalette(palette1);
        label_2->setFont(font2);
        user = new QLabel(centralwidget);
        user->setObjectName("user");
        user->setGeometry(QRect(110, 230, 291, 31));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        user->setPalette(palette2);
        user->setFont(font);
        ViewUser->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ViewUser);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        ViewUser->setMenuBar(menubar);
        statusbar = new QStatusBar(ViewUser);
        statusbar->setObjectName("statusbar");
        ViewUser->setStatusBar(statusbar);

        retranslateUi(ViewUser);

        QMetaObject::connectSlotsByName(ViewUser);
    } // setupUi

    void retranslateUi(QMainWindow *ViewUser)
    {
        ViewUser->setWindowTitle(QCoreApplication::translate("ViewUser", "MainWindow", nullptr));
        nombre->setText(QCoreApplication::translate("ViewUser", "Name: ", nullptr));
        apellido->setText(QCoreApplication::translate("ViewUser", "Lastname: ", nullptr));
        rol->setText(QCoreApplication::translate("ViewUser", "Role:", nullptr));
        ultimaActividad->setText(QCoreApplication::translate("ViewUser", "Last activity:", nullptr));
        pushButton1_2->setText(QCoreApplication::translate("ViewUser", "Return", nullptr));
        label->setText(QCoreApplication::translate("ViewUser", "View user information", nullptr));
        label_2->setText(QCoreApplication::translate("ViewUser", "Select an user", nullptr));
        user->setText(QCoreApplication::translate("ViewUser", "Username: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewUser: public Ui_ViewUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWUSER_H
