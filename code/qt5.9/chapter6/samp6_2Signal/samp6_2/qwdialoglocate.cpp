#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"
#include "mainwindow.h"
#include <QMessageBox>

QWDialogLocate::QWDialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogLocate)
{
    ui->setupUi(this);
}

QWDialogLocate::~QWDialogLocate()
{
    QMessageBox::information(this, "提示", "单元格定位对话框被删除");
    delete ui;
}

void QWDialogLocate::closeEvent(QCloseEvent *e)
{
    emit changeActionEnable(true);
}

void QWDialogLocate::showEvent(QShowEvent *e)
{
    emit changeActionEnable(false);
}

void QWDialogLocate::on_btnClose_clicked()
{
}

void QWDialogLocate::on_btnSetText_clicked()
{
    int row = ui->spinBoxRow->value();
    int column = ui->spinBoxColumn->value();
    QString text = ui->editCaption->text();
    if(ui->chkBoxRow->isChecked())
        ui->spinBoxRow->setValue(1+row);
    if(ui->chkBoxColumn->isChecked())
        ui->spinBoxColumn->setValue(1+column);

    emit setACellContent(row, column, text);
}

void QWDialogLocate::setRowColumn(int row, int column)
{
    ui->spinBoxRow->setValue(row);
    ui->spinBoxColumn->setValue(column);
}

