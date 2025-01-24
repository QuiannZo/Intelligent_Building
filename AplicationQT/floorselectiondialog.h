#ifndef FLOORSELECTIONDIALOG_H
#define FLOORSELECTIONDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <qstring.h>

class FloorSelectionDialog : public QDialog {
    Q_OBJECT

public:
    explicit FloorSelectionDialog(QWidget *parent = nullptr);
    void getSelectedFloors(int8_t floorsArray[], int maxSize) const;

private:
    QList<QCheckBox*> floorCheckboxes;
};

#endif // FLOORSELECTIONDIALOG_H

