#include "mainwindow.h"

#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "../etapa4/etapa4PI/UserNode.hpp"

int main(int argc, char *argv[])
{
    // Crear un objeto `userHandler` que se le va a pasar como referencia
    // a la pantalla principal y a las subsiguientes.
    ClientNode* clientNode = new ClientNode("client_log_file.txt", 2);
    UserNode* userHandler = new UserNode("users_log_file.txt", 2, "usersData.txt", 3001);
    // crear aplicación de QT
    QApplication a(argc, argv);
    // se debe desreferenciar el puntero
    MainWindow w = MainWindow(nullptr, *userHandler, *clientNode);
    w.show();

    int result = a.exec();
    delete userHandler;
    std::cout << "Application closed." << std::endl;
    return result;
}
