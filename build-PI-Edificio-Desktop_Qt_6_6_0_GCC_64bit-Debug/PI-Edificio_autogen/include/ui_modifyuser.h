/********************************************************************************
** Form generated from reading UI file 'modifyuser.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYUSER_H
#define UI_MODIFYUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModifyUser
{
public:
    QWidget *centralwidget;
    QWidget *widgetUser;
    QLabel *nombre;
    QPushButton *pushButton1;
    QPushButton *pushButton1_2;
    QComboBox *comboBox;
    QRadioButton *buildingMng;
    QRadioButton *dbAdm;
    QRadioButton *Auditor;
    QRadioButton *floorMng;
    QRadioButton *systemAd;
    QRadioButton *userAd;
    QLabel *role;
    QLabel *name;
    QLabel *lastName;
    QLabel *username;
    QLineEdit *lastNamelineEdit;
    QLineEdit *namelineEdit;
    QLineEdit *usernamelineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ModifyUser)
    {
        if (ModifyUser->objectName().isEmpty())
            ModifyUser->setObjectName("ModifyUser");
        ModifyUser->resize(1000, 600);
        centralwidget = new QWidget(ModifyUser);
        centralwidget->setObjectName("centralwidget");
        widgetUser = new QWidget(centralwidget);
        widgetUser->setObjectName("widgetUser");
        widgetUser->setGeometry(QRect(420, 20, 81, 71));
        nombre = new QLabel(centralwidget);
        nombre->setObjectName("nombre");
        nombre->setGeometry(QRect(400, 100, 121, 31));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        nombre->setPalette(palette);
        QFont font;
        font.setPointSize(16);
        font.setBold(false);
        nombre->setFont(font);
        pushButton1 = new QPushButton(centralwidget);
        pushButton1->setObjectName("pushButton1");
        pushButton1->setGeometry(QRect(390, 510, 151, 41));
        QFont font1;
        font1.setBold(true);
        pushButton1->setFont(font1);
        pushButton1->setStyleSheet(QString::fromUtf8("    QPushButton {\n"
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
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(380, 140, 161, 26));
        buildingMng = new QRadioButton(centralwidget);
        buildingMng->setObjectName("buildingMng");
        buildingMng->setGeometry(QRect(220, 460, 131, 23));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        buildingMng->setPalette(palette1);
        QFont font2;
        font2.setBold(false);
        buildingMng->setFont(font2);
        dbAdm = new QRadioButton(centralwidget);
        dbAdm->setObjectName("dbAdm");
        dbAdm->setGeometry(QRect(380, 430, 191, 23));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        dbAdm->setPalette(palette2);
        dbAdm->setFont(font2);
        Auditor = new QRadioButton(centralwidget);
        Auditor->setObjectName("Auditor");
        Auditor->setGeometry(QRect(580, 460, 171, 23));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        Auditor->setPalette(palette3);
        Auditor->setFont(font2);
        floorMng = new QRadioButton(centralwidget);
        floorMng->setObjectName("floorMng");
        floorMng->setGeometry(QRect(580, 430, 191, 23));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        floorMng->setPalette(palette4);
        floorMng->setFont(font2);
        systemAd = new QRadioButton(centralwidget);
        systemAd->setObjectName("systemAd");
        systemAd->setGeometry(QRect(380, 460, 171, 23));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        systemAd->setPalette(palette5);
        systemAd->setFont(font2);
        userAd = new QRadioButton(centralwidget);
        userAd->setObjectName("userAd");
        userAd->setGeometry(QRect(220, 430, 161, 23));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        userAd->setPalette(palette6);
        userAd->setFont(font2);
        role = new QLabel(centralwidget);
        role->setObjectName("role");
        role->setGeometry(QRect(440, 390, 51, 31));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        role->setPalette(palette7);
        role->setFont(font);
        name = new QLabel(centralwidget);
        name->setObjectName("name");
        name->setGeometry(QRect(430, 260, 61, 31));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        name->setPalette(palette8);
        name->setFont(font);
        lastName = new QLabel(centralwidget);
        lastName->setObjectName("lastName");
        lastName->setGeometry(QRect(410, 320, 101, 31));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        lastName->setPalette(palette9);
        lastName->setFont(font);
        username = new QLabel(centralwidget);
        username->setObjectName("username");
        username->setGeometry(QRect(410, 200, 101, 31));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        username->setPalette(palette10);
        username->setFont(font);
        lastNamelineEdit = new QLineEdit(centralwidget);
        lastNamelineEdit->setObjectName("lastNamelineEdit");
        lastNamelineEdit->setGeometry(QRect(350, 350, 221, 26));
        namelineEdit = new QLineEdit(centralwidget);
        namelineEdit->setObjectName("namelineEdit");
        namelineEdit->setGeometry(QRect(350, 290, 221, 26));
        usernamelineEdit = new QLineEdit(centralwidget);
        usernamelineEdit->setObjectName("usernamelineEdit");
        usernamelineEdit->setGeometry(QRect(350, 230, 221, 26));
        ModifyUser->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ModifyUser);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 23));
        ModifyUser->setMenuBar(menubar);
        statusbar = new QStatusBar(ModifyUser);
        statusbar->setObjectName("statusbar");
        ModifyUser->setStatusBar(statusbar);

        retranslateUi(ModifyUser);

        QMetaObject::connectSlotsByName(ModifyUser);
    } // setupUi

    void retranslateUi(QMainWindow *ModifyUser)
    {
        ModifyUser->setWindowTitle(QCoreApplication::translate("ModifyUser", "MainWindow", nullptr));
        nombre->setText(QCoreApplication::translate("ModifyUser", "Cambiar rol:", nullptr));
        pushButton1->setText(QCoreApplication::translate("ModifyUser", "Guardar", nullptr));
        pushButton1_2->setText(QCoreApplication::translate("ModifyUser", "Return", nullptr));
        buildingMng->setText(QCoreApplication::translate("ModifyUser", "Bulding Manager", nullptr));
        dbAdm->setText(QCoreApplication::translate("ModifyUser", "Database Administrator", nullptr));
        Auditor->setText(QCoreApplication::translate("ModifyUser", "Auditor", nullptr));
        floorMng->setText(QCoreApplication::translate("ModifyUser", "Floor Manager", nullptr));
        systemAd->setText(QCoreApplication::translate("ModifyUser", "System administrator", nullptr));
        userAd->setText(QCoreApplication::translate("ModifyUser", "User Administrator", nullptr));
        role->setText(QCoreApplication::translate("ModifyUser", "Role", nullptr));
        name->setText(QCoreApplication::translate("ModifyUser", "Name", nullptr));
        lastName->setText(QCoreApplication::translate("ModifyUser", "Last Name", nullptr));
        username->setText(QCoreApplication::translate("ModifyUser", "Username", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModifyUser: public Ui_ModifyUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYUSER_H
