#include "removeuser.h"
#include "ui_removeuser.h"

RemoveUser::RemoveUser(QWidget *parent, UserNode& userHandler, menuwindow& menu)
    : QMainWindow(parent)
    , ui(new Ui::RemoveUser), userHandler(userHandler), menu(menu)
{
    ui->setupUi(this);

    //Fondos para los widgets y mainw.
    // Load background.
    QPalette palette;
    QPixmap bkgnd(":/resource/img/img1.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    palette.setBrush(QPalette::Window, bkgnd);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    // userWidget
    QString path2 = ":/resource/img/remove-user.png";
    QPixmap bkgnd2(path2);

    if (!bkgnd2.isNull()) {
        bkgnd2 = bkgnd2.scaled(ui->widgetUser->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd2);
        ui->widgetUser->setAutoFillBackground(true);
        ui->widgetUser->setPalette(palette);
    } else {
        qDebug() << "Error: no se pudo cargar la imagen";
    }

    //
    // Cargar usuarios
    loadUserList();

    // Conectar la selección de usuario en QListWidget
    connect(ui->listWidget, &QListWidget::itemClicked, this, &RemoveUser::on_listWidget_itemClicked);
}

void RemoveUser::loadUserList() {
    // Abrir el archivo CSV y cargar los usernames en QListWidget
    std::string filep = userHandler.getUsersFile();
    QFile file = (QString::fromStdString(filep));  // Cambia a la ruta de tu archivo
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        in.readLine(); // Ignora la primera línea de cabecera

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList userInfo = line.split(',');
            if (userInfo.size() >= 1) {
                ui->listWidget->addItem(userInfo[0]); // Añade solo el username
            }
        }
    }
    file.close();
}

RemoveUser::~RemoveUser()
{
    delete ui;
}

void RemoveUser::on_pushButton1_2_clicked()
{
    this->menu.show();
    this->hide();
    this->deleteLater();
}


void RemoveUser::on_listWidget_itemClicked(QListWidgetItem *item)
{
    selectedUser = item->text();
}


void RemoveUser::on_pushButton1_clicked()
{
    // Verifica que hay un usuario seleccionado
    if (selectedUser.isEmpty()) {
        qDebug() << "No se ha seleccionado ningún usuario para eliminar.";
            return;
    }

    // Llama a la función para eliminar el usuario utilizando UserHandler
    if (userHandler.deleteUser("admin", selectedUser.toStdString())) {
        qDebug() << "Usuario eliminado con éxito.";

                    // Actualiza la lista de usuarios en la interfaz
                    ui->listWidget->clear();
        loadUserList();  // Vuelve a cargar la lista de usuarios
    } else {
        qDebug() << "Error al eliminar el usuario.";
    }
}

