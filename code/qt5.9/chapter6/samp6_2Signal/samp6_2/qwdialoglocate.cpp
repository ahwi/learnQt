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
