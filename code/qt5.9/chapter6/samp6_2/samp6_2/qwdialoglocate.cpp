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

//窗口关闭事件,关闭时释放本窗口
void QWDialogLocate::closeEvent(QCloseEvent *event)
{
    MainWindow *parWind = (MainWindow *)parentWidget();	//获取主窗口
    parWind->setActLocateEnable(true);
    parWind->setDlgLocateNull();
}

//窗口显示事件
void QWDialogLocate::showEvent(QShowEvent *event)
{
    MainWindow *parWind = (MainWindow *)parentWidget();	//获取主窗口
    parWind->setActLocateEnable(false);
}

void QWDialogLocate::setSpinRange(int rowCount, int colCount)
{
    ui->spinBoxRow->setMaximum(rowCount-1);
    ui->spinBoxColumn->setMaximum(colCount-1);
}


void QWDialogLocate::setSpinValue(int rowNo, int colNo)
{
    ui->spinBoxRow->setValue(rowNo);
    ui->spinBoxColumn->setValue(colNo);
}

void QWDialogLocate::on_btnClose_clicked()
{
    int row = ui->spinBoxRow->value();
    int column = ui->spinBoxColumn->value();

    MainWindow *parWind = (MainWindow *)parentWidget();	//获取主窗口
    parWind->setACellText(row, column, ui->editCaption->text());	//设置单元格文字

    if(ui->chkBoxRow->isChecked()) //行增
        ui->spinBoxRow->setValue(1+ui->spinBoxRow->value());

    if(ui->chkBoxColumn->isChecked()) //列增
        ui->spinBoxColumn->setValue(1+ui->spinBoxColumn->value());
}
