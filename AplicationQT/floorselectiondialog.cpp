#include "floorselectiondialog.h"

FloorSelectionDialog::FloorSelectionDialog(QWidget *parent)
    : QDialog(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Crear checkboxes para cada piso
    for (int i = 1; i <= 32; ++i) {
        QCheckBox *checkbox = new QCheckBox("Floor " + QString::number(i), this);
        layout->addWidget(checkbox);
        floorCheckboxes.append(checkbox);
    }

    // Botón para confirmar selección
    QPushButton *confirmButton = new QPushButton("Confirm", this);
    layout->addWidget(confirmButton);
    connect(confirmButton, &QPushButton::clicked, this, &QDialog::accept);
}

void FloorSelectionDialog::getSelectedFloors(int8_t floorsArray[], int maxSize) const {
    int count = 0;
    for (int i = 0; i < floorCheckboxes.size() && count < maxSize; ++i) {
        if (floorCheckboxes[i]->isChecked()) {
            floorsArray[count++] = static_cast<int8_t>(i + 1); // Guardar el piso seleccionado en el arreglo
        }
    }
    // Rellenar el resto del arreglo con ceros si hay espacios sin usar
    for (int i = count; i < maxSize; ++i) {
        floorsArray[i] = 0;
    }
}
