#include <cstring>
#include <iostream>
#include "Authenticator.hpp"
#include "DataCollector.hpp"
#include "FAT.hpp"
#include "Usuario.hpp"
#include "HashHandler.hpp"
#include "Log.hpp"
#include "UserHandler.hpp"

using namespace std;

int main() {
    /*
    Authenticator objectA;
    FAT* objectFAT = objectA.getData();
    char *filename = (char *)"users.txt";
    char *date = (char *)"12/12/2012";
    objectFAT->create(filename, date);
    objectFAT->open(filename, 7);
    // Presentación PI

    std::cout << "********** (1) Imprimir antes de crear archivos y agregar usuarios (1) **********" << std::endl << std::endl;
    //objectFAT->print(true);
    std::cout << std::endl;
    std::cout << "********** (2) Imprimir después de crear archivos (2) **********" << std::endl << std::endl;
    objectFAT->create(filename, date);
    //objectFAT->print(true);
    objectFAT->open(filename, 7);
    std::cout << std::endl;

    Usuario myUser;

    std::cout << "********** (3) Imprimir después de agregar usuarios (3) **********" << std::endl << std::endl;
    objectFAT->write(filename, 7, (char*)"Chanchito hx9242\n");
    objectFAT->append(filename, 7, (char*)"Papita z22342\n");
    myUser.addUser("admin", "root1234", "1", "Quiann", "ZOlfaghari", "118700209", filename, objectFAT);
    //objectFAT->print(true);
    std::cout << std::endl;
    //myUser.print(true);

    std::cout << "********** (4) Verificación (4) **********" << std::endl << std::endl;
    bool autenticado = objectA.autenticar((char *)"admin", (char *)"urrw");
    if (autenticado) {
        std::cout << "admin" << ": usuario verificado!" << std::endl;
    } else { 
        std::cout << "admin" << ": usuario no verificado!" << std::endl;
    }
    autenticado = objectA.autenticar((char *)"Papita", (char *)"z22342");
    if (autenticado) {
        std::cout << "Papita" << ": usuario verificado!" << std::endl;
    } else { 
        std::cout << "Papita" << ": usuario no verificado!" << std::endl;
    }

    objectFAT->loadFile((char *)"FormatoBitacora.txt", 7);
    objectFAT->print(true);

    objectFAT->open((char *)"FormatoBitacora.txt", 8);
    if(objectFAT->saveFile((char *)"FormatoBitacora.txt", 8, (char *)"proof.txt")) {
        std::cout << "Guardado exitosamente" << std::endl;
    }
    objectFAT->close((char *)"FormatoBitacora.txt", 8);
    // get line
    objectFAT->open((char *)"FormatoBitacora.txt", 8);
    char buffer[200];
    objectFAT->getLine((char *)"FormatoBitacora.txt", buffer, 200, 8);
    std::cout << buffer;
    objectFAT->getLine((char *)"FormatoBitacora.txt", buffer, 200, 8);
    std::cout << buffer;
    objectFAT->close((char *)"FormatoBitacora.txt", 8);
    std::cout << "Tamaño del archivo en chrs " <<  objectFAT->getFileSize((char *)"FormatoBitacora.txt") << std::endl;

    HashHandler hashHandler = HashHandler();
    string hash = hashHandler.generateHASH_SHA256((string)"password1234+");
    std::cout << "HASH: " << hash << std::endl;
    if (hashHandler.validatePassword_SHA256((string)"password1234+", hash)) {
        std::cout << "Se validó la contraseña." << std::endl;
    } else {
        std::cout << "No se validó la contraseña." << std::endl;
    }
    // 
    if (hashHandler.validatePassword_SHA256((string)"password4567+", hash)) {
        std::cout << "Se validó la contraseña." << std::endl;
    } else {
        std::cout << "No se validó la contraseña." << std::endl;
    }
    */
    //Log log = Log("file_proof1.txt", 2);
    //cout << "LOG: " << log.returnLog((std::string)"jose") << std::endl;
    DataCollector sensor = DataCollector("sensors_log_file.txt", 2, "sensorsData.txt");
    UserHandler userHandler = UserHandler("users_log_file.txt", 2, "usersData.txt");
    std::string error;
    if (userHandler.authenticateUser("username01", userHandler.generateHash("password01"), error)) {
        std::cout << "Usuario validado." << std::endl;
    } else {
        std::cout << "Usuario no validado." << std::endl;
    }

    if (userHandler.authenticateUser("username02", userHandler.generateHash("password03"), error)) {
        std::cout << "Usuario validado." << std::endl;
    } else {
        std::cout << "Usuario no validado." << std::endl;
    }

    if (userHandler.authenticateUser("username03", userHandler.generateHash("password03"), error)) {
        std::cout << "Usuario validado." << std::endl;
    } else {
        std::cout << "Usuario no validado." << std::endl;
    }

    if (userHandler.hasPermissions("username01", USER_ADMINISTRATOR)) {
        std::cout << "Tiene permisos" << std::endl;
    } else {
        std::cout << "No tiene permisos." << std::endl;
    }

    if (userHandler.hasPermissions("username02", AUDITOR)) {
        std::cout << "Tiene permisos" << std::endl;
    } else {
        std::cout << "No tiene permisos." << std::endl;
    }

    
    if (userHandler.hasPermissions("username10", DATABASE_ADMINISTRATOR)) {
        std::cout << "Tiene permisos" << std::endl;
    } else {
        std::cout << "No tiene permisos." << std::endl;
    }


    /*
    sensor.returnSensorFile("jose");
    
    UserHandler userHandler = UserHandler("users_log_file.txt", 2, "usersData.txt");

    userHandler.addUser("superUser", "username01", userHandler.generateHash("password01")
                        , USER_ADMINISTRATOR, "", "name01", "lastName01", "00000001");
    userHandler.addUser("superUser", "username02", userHandler.generateHash("password02")
                        , DATABASE_ADMINISTRATOR, "", "name02", "lastName02", "00000002");
    userHandler.addUser("superUser", "username03", userHandler.generateHash("password03")
                        , FLOOR_MANAGER, "2&3", "name03", "lastName03", "00000003");
    userHandler.addUser("superUser", "username03", userHandler.generateHash("password03")
                        , BUILDING_MANAGER, "", "name04", "lastName04", "00000004");
    userHandler.addUser("superUser", "username04", userHandler.generateHash("password04")
                        , SYSTEM_ADMINISTRATOR, "", "name01", "lastName01", "00000001");
    userHandler.addUser("superUser", "username05", userHandler.generateHash("password05")
                        , AUDITOR, "", "name05", "lastName05", "00000005");
    userHandler.addUser("superUser", "username06", userHandler.generateHash("password06")
                        , USER_ADMINISTRATOR | DATABASE_ADMINISTRATOR, "", "name06", "lastName06", "00000006"); 
    userHandler.addUser("superUser", "username07", userHandler.generateHash("password07")
                        , SYSTEM_ADMINISTRATOR | AUDITOR, "", "name07", "lastName07", "00000007"); 
    userHandler.addUser("superUser", "username08", userHandler.generateHash("password08")
                        , FLOOR_MANAGER, "4&5&6&7", "name08", "lastName08", "00000008"); 
    userHandler.addUser("superUser", "username09", userHandler.generateHash("password09")
                        , USER_ADMINISTRATOR, "", "name09", "lastName09", "00000009");      
    userHandler.addUser("superUser", "username10", userHandler.generateHash("password10")
                        , USER_ADMINISTRATOR | DATABASE_ADMINISTRATOR | AUDITOR, "", "name10", "lastName10", "00000010");       
    */
    return 0;
}