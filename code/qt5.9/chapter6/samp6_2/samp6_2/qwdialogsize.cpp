#include "qwdialogsize.h"
#include "ui_qwdialogsize.h"

QWDialogSize::QWDialogSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogSize)
{
    ui->setupUi(this);
}

QWDialogSize::~QWDialogSize()
{
    delete ui;
}


int QWDialogSize::rowCount()
{
    return ui->spinBoxRow->value();
}

int QWDialogSize::columnCount()
{
    return ui->spinBoxColumn->value();
}

void QWDialogSize::setRowColumn(int row, int column)
{
    ui->spinBoxRow->setValue(row);
    ui->spinBoxColumn->setValue(column);
}
