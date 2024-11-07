#include "floorselectiondialog.h"

FloorSelectionDialog::FloorSelectionDialog(QWidget *parent)
    : QDialog(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Crear checkboxes para cada piso
    for (int i = 1; i <= 7; ++i) {
        QCheckBox *checkbox = new QCheckBox("Floor " + QString::number(i), this);
        layout->addWidget(checkbox);
        floorCheckboxes.append(checkbox);
    }

    // Botón para confirmar selección
    QPushButton *confirmButton = new QPushButton("Confirm", this);
    layout->addWidget(confirmButton);
    connect(confirmButton, &QPushButton::clicked, this, &QDialog::accept);
}

QString FloorSelectionDialog::getSelectedFloors() const {
    QStringList selectedFloors;
    for (int i = 0; i < floorCheckboxes.size(); ++i) {
        if (floorCheckboxes[i]->isChecked()) {
            selectedFloors << QString::number(i + 1);
        }
    }
    return "" + selectedFloors.join("&") + "";
}
