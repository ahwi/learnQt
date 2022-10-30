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
