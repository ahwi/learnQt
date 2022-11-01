#include "qwdialogheaders.h"
#include "ui_qwdialogheaders.h"
#include <QMessageBox>

QWDialogHeaders::QWDialogHeaders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogHeaders)
{
    ui->setupUi(this);

    theModel = new QStringListModel;
    ui->listView->setModel(theModel);
}

QWDialogHeaders::~QWDialogHeaders()
{
    QMessageBox::information(this, "提示", "设置表头标题对话框被删除");
    delete ui;
}

void QWDialogHeaders::setHeaderList(QStringList &headers)
{
    theModel->setStringList(headers);
}

QStringList QWDialogHeaders::headerList()
{
    return theModel->stringList();
}
