#include "mainwindow.h"

#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "../UserHandler.hpp"

int main(int argc, char *argv[])
{
    // Crear un objeto `userHandler` que se le va a pasar como referencia
    // a la pantalla principal y a las subsiguientes.
    UserHandler* userHandler = new UserHandler("users_log_file.txt", 2, "usersData.txt");
    // crear aplicación de QT
    QApplication a(argc, argv);
    // se debe desreferenciar el puntero
    MainWindow w = MainWindow(nullptr, *userHandler);
    w.show();

    int result = a.exec();
    delete userHandler;
    std::cout << "Application closed." << std::endl;
    return result;
}
