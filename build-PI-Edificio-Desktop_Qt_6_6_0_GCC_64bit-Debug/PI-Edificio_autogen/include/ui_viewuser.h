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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewUser
{
public:
    QWidget *centralwidget;
    QWidget *widgetUser;
    QLabel *nombre;
    QLabel *apellido;
    QLabel *rol;
    QLabel *ultimaActividad;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ViewUser)
    {
        if (ViewUser->objectName().isEmpty())
            ViewUser->setObjectName("ViewUser");
        ViewUser->resize(1000, 600);
        centralwidget = new QWidget(ViewUser);
        centralwidget->setObjectName("centralwidget");
        widgetUser = new QWidget(centralwidget);
        widgetUser->setObjectName("widgetUser");
        widgetUser->setGeometry(QRect(390, 40, 171, 151));
        nombre = new QLabel(centralwidget);
        nombre->setObjectName("nombre");
        nombre->setGeometry(QRect(340, 220, 251, 31));
        QFont font;
        font.setPointSize(16);
        nombre->setFont(font);
        apellido = new QLabel(centralwidget);
        apellido->setObjectName("apellido");
        apellido->setGeometry(QRect(340, 260, 251, 31));
        apellido->setFont(font);
        rol = new QLabel(centralwidget);
        rol->setObjectName("rol");
        rol->setGeometry(QRect(340, 300, 251, 31));
        rol->setFont(font);
        ultimaActividad = new QLabel(centralwidget);
        ultimaActividad->setObjectName("ultimaActividad");
        ultimaActividad->setGeometry(QRect(340, 340, 251, 31));
        ultimaActividad->setFont(font);
        ViewUser->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ViewUser);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
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
        nombre->setText(QCoreApplication::translate("ViewUser", "Nombre:", nullptr));
        apellido->setText(QCoreApplication::translate("ViewUser", "Apellido: ", nullptr));
        rol->setText(QCoreApplication::translate("ViewUser", "Rol:", nullptr));
        ultimaActividad->setText(QCoreApplication::translate("ViewUser", "\303\232ltima actividad:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewUser: public Ui_ViewUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWUSER_H
