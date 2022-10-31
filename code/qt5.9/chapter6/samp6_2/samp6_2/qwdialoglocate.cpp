#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"

QWDialogLocate::QWDialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogLocate)
{
    ui->setupUi(this);
}

QWDialogLocate::~QWDialogLocate()
{
    delete ui;
}
