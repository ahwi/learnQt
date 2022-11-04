#include "qformtable.h"
#include "ui_qformtable.h"


QFormTable::QFormTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QFormTable)
{
    ui->setupUi(this);

    // 设置数据模型、选择模型
    theModel = new QStandardItemModel(12, 6, this);
    theSelection = new QItemSelectionModel(theModel);
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
}

QFormTable::~QFormTable()
{
    delete ui;
}
