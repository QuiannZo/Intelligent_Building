#include "viewdatabasewindow.h"
#include "ui_viewdatabasewindow.h"

viewdatabasewindow::viewdatabasewindow(QWidget *parent, UserNode& userHandler, menuwindow& menu, ClientNode& clientNode) :
    QMainWindow(parent),
    ui(new Ui::viewdatabasewindow), userHandler(userHandler), menu(menu), clientNode(clientNode)
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

    // Botones.
    // icono y el texto
    QString path3 = ":/resource/img/sensor.png";
    ui->pushButton8->setIcon(QIcon(path3));
    ui->pushButton8->setIconSize(QSize(48, 48));

}
viewdatabasewindow::~viewdatabasewindow()
{
    delete ui;
}


void viewdatabasewindow::on_pushButton1_2_clicked()
{
    this->menu.show();
    this->hide();
    this->deleteLater();
}


void viewdatabasewindow::on_pushButton8_clicked() // Sensors.
{
    std::string response;
    clientNode.getSensorData(this->clientNode.username, response);

    // Convertimos la respuesta de std::string a QString
    QString responseStr = QString::fromStdString(response);

    // Dividimos la respuesta en líneas (cada sensor será una línea)
    QStringList lines = responseStr.split("\n");

    // Establecemos el número de filas y columnas en la tabla
    int rowCount = lines.size();
    int colCount = 4; // Sabemos que hay 4 columnas: idSensor, date, time, value

    // Configuramos la tabla con las filas y columnas
    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(colCount);

    // Establecemos los encabezados de las columnas
    QStringList headers = {"idSensor", "Date", "Time", "Value"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Rellenamos la tabla con los datos de cada fila
    for (int i = 0; i < rowCount; ++i) {
        QStringList fields = lines[i].split(",");

        // Aseguramos que la línea tenga el número correcto de columnas
        if (fields.size() == colCount) {
            // Insertamos los datos de cada columna en las filas correspondientes
            for (int j = 0; j < fields.size(); ++j) {
                QTableWidgetItem *item = new QTableWidgetItem(fields[j].trimmed());  // trim() elimina espacios extra
                ui->tableWidget->setItem(i, j, item);
            }
        }
    }

    // Ajusta el ancho de las columnas automáticamente para que se ajusten al contenido
    ui->tableWidget->resizeColumnsToContents();

    // Estira la última columna para que ocupe el espacio sobrante
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

