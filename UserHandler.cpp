#include "UserHandler.hpp"

UserHandler::UserHandler(std::string logFilename, int processId, std::string usersFilename) 
: Log(logFilename, processId), usersFilename(usersFilename) {
    this->hashHandler = new HashHandler();
    //TODO: está sección presenta código repetido con el CollectionHandler, considerar mover esto a la clase base "log".
    bool fileCreated = false;
    bool error = false;
    // Try opening the file in read mode to check if it exists
    std::ifstream fileCheck(usersFilename.c_str());
    if (fileCheck) {
        std::cout << "File '" <<  usersFilename << "' already exists, it will be loaded into the file system." << std::endl;
        fileCheck.close();
    } else {
        // Create the file if it doesn't exist
        std::ofstream file(usersFilename);
        if (file) {
            std::cout << "File created: " << usersFilename << std::endl;
            file.close();
            fileCreated = true;
        } else {
            std::cerr << "Error creating file: " << usersFilename << std::endl;
            error = true;
        }
    }
    // load file into our filesystem 
    if (!error) {
        std::ostringstream output;
        if (this->fileSystem->loadFile((char*)usersFilename.c_str(), processId)) {
            if (fileCreated) {
                output << "File '" << usersFilename << "' <Type:File-user-data> created and loaded into filesystem.";
            } else {
                output << "File '" << usersFilename << "' <Type:File-user-data> loaded into filesystem.";
            }   
            if(!this->fileSystem->open((char*)usersFilename.c_str(), defaultProcessId)) {
                std::cerr << "Error <filesystem>: could not open file '" <<  usersFilename << "'.\n";
            } else {
                if (fileCreated) {
                    if (!this->fileSystem->append((char*)usersFilename.c_str(), this->getProcessId() 
                        ,(char*)"username,hash,permissions,[floors],name,lastName,userId,createdDate,lastUpdateDate,isActive\n")) {
                            std::cerr << "Error: could not append to '" << usersFilename << "'."  << std::endl;
                        }
                }
            }
            if (!this->appendToLogTimeHour(output.str())) {
                std::cerr << "Error: could not append to '" << usersFilename << "'."  << std::endl;
            }
        } else {
            std::cerr << "Error: could not open file " << usersFilename << std::endl;
        }
    }
}

UserHandler::~UserHandler() {
    // save log before destroy object 
    this->fileSystem->saveFile((char*)usersFilename.c_str(), defaultProcessId, (char*)usersFilename.c_str());
    this->fileSystem->close((char*)usersFilename.c_str(), defaultProcessId);
    std::ostringstream output;
    output << "Users data file closed and saved to file '" << usersFilename << "'.";
    this->appendToLogTimeHour(output.str());

    delete this->hashHandler;
}

std::vector<std::string> UserHandler::splitString(const char* input) {
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string token;
    // separate string by commas
    while (std::getline(ss, token, ',')) {
        result.push_back(token);
    }
    return result;
}

std::string UserHandler::vectorToString(const std::vector<std::string> &vec) {
        std::stringstream result;
    for (size_t i = 0; i < vec.size(); ++i) {
        result << vec[i];
        if (i != vec.size() - 1) {
            result << ",";  // separate by comma
        } //else {
            //result << "\n";  // add \n at the end
        //}
    }
    return result.str();
}

bool UserHandler::addUser(const std::string &addedByUser, const std::string &username, const std::string &hash, const uint8_t permissions
, const std::string& floors, const std::string &name, const std::string &lastName, const std::string &userId) {
    // TODO: EVITAR que se puedan agregar dos usuarios con el mismo nombre.
    std::string dateTime = this->getCurrentDateTime();
    //"username,hash,permissions,[floors],name,lastName,userId,createdDate,lastUpdateDate,isActive"
    std::string concatenated = username + "," + hash + "," + std::to_string(permissions) + ",[" 
                                + floors + "],"
                                + name + "," + lastName + "," + userId + ","
                                + dateTime + "," + dateTime // created and updated
                                + ",1\n"; //  the `1` is used to indicate that the user is active 
    if(concatenated.empty()) {
        return false;
    }
    // add the new user to the filesystem 
    bool result = this->fileSystem->append((char*)usersFilename.c_str(), this->getProcessId(), (char*)concatenated.c_str());
    if (result) {
        this->appendToLogTimeHour(
            "New user: '" + addedByUser + "' added [Username: " + username 
                        + " | Name: " + name + " " + lastName
                        + " | Permissions: " + std::to_string(permissions) + "].");
    } else {
        this->appendToLogTimeHour(
            "New user [failed] [probably error related to append() of the file system]: '" 
                        + addedByUser + "' tried to add [Username: " + username 
                        + " | Name: " + name + " " + lastName
                        + " | Permissions: " + std::to_string(permissions) + "].");
    }
    return result;
}

bool UserHandler::authenticateUser(const std::string &username, const std::string &hash, std::string &error) {
    if (this->fileSystem->resetFileCursors((char*)this->usersFilename.c_str())) {
        this->appendToLogTimeHour("[Log-in]: attempting to authenticate '" + username + "'.");
        char buffer[1024] = {};
        // ignore first line
        this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                                , buffer, 1000, this->defaultProcessId);
        bool result = this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                                , buffer, 1000, this->defaultProcessId);
        bool stop = !result;
        bool userFound = false;
        bool hashValidated = false;
        while (!stop) {
            if(result) {
                std::vector<std::string> stringVector = this->splitString(buffer);
                if (stringVector.size() != 10) {
                    stop = true;
                } else {
                    if (stringVector[0] == username) {
                        userFound = true;
                        if (stringVector[1] == hash) {
                            hashValidated = true;
                        }
                        stop = true;
                    } else {
                        result = this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                                , buffer, 1000, this->defaultProcessId);
                    }
                } 
            } else {
                stop = true;
            }  
        }
        if (hashValidated) {
            this->appendToLogTimeHour("[Log-in]: user '" + username + "' validated.");
        } else {
            if (userFound) {
                this->appendToLogTimeHour("[Log-in]: invalid hash for user '" + username + "'.");
                error = "invalid_password";
            } else {
                this->appendToLogTimeHour("[Log-in]: user '" + username + "' not found.");
                error = "invalid_username";
            }
        }
        return hashValidated;
    }
    return false;
}

std::string UserHandler::generateHash(const std::string &password) {
    return this->hashHandler->generateHASH_SHA256(password);
}

bool UserHandler::hasPermissions(const std::string &username, permissions role) {
    std::vector<std::string> user = getUserInformation(username);
    if (user.size() == 10) {
        uint8_t userPermission = static_cast<uint8_t>(std::stoi(user[2]));
        if ((userPermission & role) == role) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> UserHandler::getUserInformation(const std::string &username) {
    std::vector<std::string> stringVector;
    if (this->fileSystem->resetFileCursors((char *)this->usersFilename.c_str()))
    {
        this->appendToLogTimeHour("[Log-in]: attempting get information of user '" + username + "'.");
        char buffer[1024] = {};
        // ignore first line
        this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                                , buffer, 1000, this->defaultProcessId);
        bool result = this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                                , buffer, 1000, this->defaultProcessId);
        bool stop = false;
        bool userFound = false;
        while (!stop) {
            if(result) {
                stringVector = this->splitString(buffer);
                if (stringVector.size() != 10) {
                    stop = true;
                } else {
                    if (stringVector[0] == username) {
                        userFound = true;
                        stop = true;
                    } else {
                        result = this->fileSystem->getLine((char*)this->usersFilename.c_str()
                                                , buffer, 1000, this->defaultProcessId);
                    }
                } 
            } else {
                stop == true;
            }
        }
        if (userFound) {
            this->appendToLogTimeHour("[User information]: information of user '" + username + "' returned.");
        } else {
            this->appendToLogTimeHour("[User information]: user '" + username + "' not found.");
        }
    }
    return stringVector;
}

bool UserHandler::modifyUserEntry(std::string currentUserEntry, std::string newUserEntry) {
    std::string usersData;
    if (this->fileSystem->getCompleteFile((char*)this->usersFilename.c_str(), this->defaultProcessId, usersData)) {
        size_t pos = usersData.find(currentUserEntry);
        if (pos != std::string::npos) {
        // replace 
            usersData.replace(pos, currentUserEntry.length(), newUserEntry);
        }
        // rewrite the file system
        return this->fileSystem->write((char*)this->usersFilename.c_str(), this->defaultProcessId, (char*)usersData.c_str());
    }
    return false;
}
