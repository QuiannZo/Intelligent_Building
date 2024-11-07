cmake_minimum_required(VERSION 3.5)

project(PI-Edificio VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Añadir al principio del archivo CMakeLists.txt
find_package(OpenSSL REQUIRED)

# Agrega el directorio superior para que CMake encuentre UserHandler.hpp
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

message(STATUS "PROJECT_SOURCES: ${PROJECT_SOURCES}")

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ../UserHandler.cpp  # Agrega este archivo
        ../UserHandler.hpp
        ../Log.cpp
        ../Log.hpp
        ../HashHandler.cpp
        ../HashHandler.hpp
        ../Usuario.cpp
        ../Usuario.hpp
        #../UserTest.cpp
        #../main.cpp
        ../Intento.ino
        ../FAT.cpp
        ../FAT.hpp
        ../DataCollector.cpp
        ../DataCollector.hpp
        ../Authenticator.cpp
        ../Authenticator.hpp
        ../usersData.txt
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PI-Edificio
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}


        menuwindow.h menuwindow.cpp
        menuwindow.h menuwindow.cpp menuwindow.ui
        viewdatabasewindow.h viewdatabasewindow.cpp viewdatabasewindow.ui
        resource.qrc
        viewuser.h viewuser.cpp viewuser.ui
        createuser.h createuser.cpp createuser.ui
        viewlog.h viewlog.cpp viewlog.ui
        removeuser.h removeuser.cpp removeuser.ui
        modifyuser.h modifyuser.cpp modifyuser.ui
        modifydatabase.h modifydatabase.cpp modifydatabase.ui
        sensorbuilding.h sensorbuilding.cpp sensorbuilding.ui
        sensorfloor.h sensorfloor.cpp sensorfloor.ui
        viewbackup.h viewbackup.cpp viewbackup.ui
        viewnode.h viewnode.cpp viewnode.ui
        floorselectiondialog.h floorselectiondialog.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PI-Edificio APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PI-Edificio SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PI-Edificio
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Agregar OpenSSL a tu objetivo
target_link_libraries(PI-Edificio PRIVATE Qt${QT_VERSION_MAJOR}::Widgets OpenSSL::Crypto OpenSSL::SSL)

#target_link_libraries(PI-Edificio PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.PI-Edificio)
endif()
set_target_properties(PI-Edificio PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS PI-Edificio
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PI-Edificio)
endif()
