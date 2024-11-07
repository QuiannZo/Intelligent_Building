/********************************************************************************
** Form generated from reading UI file 'createuser.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEUSER_H
#define UI_CREATEUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_createuser
{
public:
    QWidget *centralwidget;
    QWidget *widgetUser;
    QLabel *username;
    QLineEdit *usernamelineEdit;
    QLabel *name;
    QLabel *password;
    QLineEdit *passwordlineEdit;
    QLineEdit *namelineEdit;
    QPushButton *createUser;
    QLineEdit *lastNamelineEdit;
    QLabel *lastName;
    QLabel *role;
    QRadioButton *userAd;
    QRadioButton *dbAdm;
    QRadioButton *floorMng;
    QPushButton *pushButton1_2;
    QRadioButton *buildingMng;
    QRadioButton *systemAd;
    QRadioButton *Auditor;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *createuser)
    {
        if (createuser->objectName().isEmpty())
            createuser->setObjectName("createuser");
        createuser->resize(1000, 600);
        centralwidget = new QWidget(createuser);
        centralwidget->setObjectName("centralwidget");
        widgetUser = new QWidget(centralwidget);
        widgetUser->setObjectName("widgetUser");
        widgetUser->setGeometry(QRect(380, 20, 171, 151));
        username = new QLabel(centralwidget);
        username->setObjectName("username");
        username->setGeometry(QRect(420, 180, 101, 31));
        QFont font;
        font.setPointSize(16);
        username->setFont(font);
        usernamelineEdit = new QLineEdit(centralwidget);
        usernamelineEdit->setObjectName("usernamelineEdit");
        usernamelineEdit->setGeometry(QRect(360, 210, 221, 26));
        name = new QLabel(centralwidget);
        name->setObjectName("name");
        name->setGeometry(QRect(440, 300, 61, 31));
        name->setFont(font);
        password = new QLabel(centralwidget);
        password->setObjectName("password");
        password->setGeometry(QRect(420, 240, 91, 31));
        password->setFont(font);
        passwordlineEdit = new QLineEdit(centralwidget);
        passwordlineEdit->setObjectName("passwordlineEdit");
        passwordlineEdit->setGeometry(QRect(360, 270, 221, 26));
        namelineEdit = new QLineEdit(centralwidget);
        namelineEdit->setObjectName("namelineEdit");
        namelineEdit->setGeometry(QRect(360, 330, 221, 26));
        createUser = new QPushButton(centralwidget);
        createUser->setObjectName("createUser");
        createUser->setGeometry(QRect(400, 540, 141, 26));
        QFont font1;
        font1.setBold(true);
        createUser->setFont(font1);
        createUser->setStyleSheet(QString::fromUtf8("    QPushButton {\n"
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
        lastNamelineEdit = new QLineEdit(centralwidget);
        lastNamelineEdit->setObjectName("lastNamelineEdit");
        lastNamelineEdit->setGeometry(QRect(360, 390, 221, 26));
        lastName = new QLabel(centralwidget);
        lastName->setObjectName("lastName");
        lastName->setGeometry(QRect(420, 360, 101, 31));
        lastName->setFont(font);
        role = new QLabel(centralwidget);
        role->setObjectName("role");
        role->setGeometry(QRect(440, 430, 51, 31));
        role->setFont(font);
        userAd = new QRadioButton(centralwidget);
        userAd->setObjectName("userAd");
        userAd->setGeometry(QRect(250, 460, 161, 23));
        dbAdm = new QRadioButton(centralwidget);
        dbAdm->setObjectName("dbAdm");
        dbAdm->setGeometry(QRect(410, 460, 191, 23));
        floorMng = new QRadioButton(centralwidget);
        floorMng->setObjectName("floorMng");
        floorMng->setGeometry(QRect(610, 460, 191, 23));
        pushButton1_2 = new QPushButton(centralwidget);
        pushButton1_2->setObjectName("pushButton1_2");
        pushButton1_2->setGeometry(QRect(10, 10, 141, 26));
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
        buildingMng = new QRadioButton(centralwidget);
        buildingMng->setObjectName("buildingMng");
        buildingMng->setGeometry(QRect(250, 490, 131, 23));
        systemAd = new QRadioButton(centralwidget);
        systemAd->setObjectName("systemAd");
        systemAd->setGeometry(QRect(410, 490, 171, 23));
        Auditor = new QRadioButton(centralwidget);
        Auditor->setObjectName("Auditor");
        Auditor->setGeometry(QRect(610, 490, 171, 23));
        createuser->setCentralWidget(centralwidget);
        menubar = new QMenuBar(createuser);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 23));
        createuser->setMenuBar(menubar);
        statusbar = new QStatusBar(createuser);
        statusbar->setObjectName("statusbar");
        createuser->setStatusBar(statusbar);

        retranslateUi(createuser);

        QMetaObject::connectSlotsByName(createuser);
    } // setupUi

    void retranslateUi(QMainWindow *createuser)
    {
        createuser->setWindowTitle(QCoreApplication::translate("createuser", "MainWindow", nullptr));
        username->setText(QCoreApplication::translate("createuser", "Username", nullptr));
        name->setText(QCoreApplication::translate("createuser", "Name", nullptr));
        password->setText(QCoreApplication::translate("createuser", "Password", nullptr));
        createUser->setText(QCoreApplication::translate("createuser", "Add User", nullptr));
        lastName->setText(QCoreApplication::translate("createuser", "Last Name", nullptr));
        role->setText(QCoreApplication::translate("createuser", "Role", nullptr));
        userAd->setText(QCoreApplication::translate("createuser", "User Administrator", nullptr));
        dbAdm->setText(QCoreApplication::translate("createuser", "Database Administrator", nullptr));
        floorMng->setText(QCoreApplication::translate("createuser", "Floor Manager", nullptr));
        pushButton1_2->setText(QCoreApplication::translate("createuser", "Return", nullptr));
        buildingMng->setText(QCoreApplication::translate("createuser", "Bulding Manager", nullptr));
        systemAd->setText(QCoreApplication::translate("createuser", "System administrator", nullptr));
        Auditor->setText(QCoreApplication::translate("createuser", "Auditor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class createuser: public Ui_createuser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEUSER_H
