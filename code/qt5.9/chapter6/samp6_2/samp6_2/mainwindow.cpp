#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    theModel = new QStandardItemModel(10, 5, this);
    theSelection = new QItemSelectionModel(theModel);

    //为tableView设置数据模型
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actTab_SetSize_triggered()
{
    QWDialogSize *dlgSetSize = new QWDialogSize(this);
    Qt::WindowFlags flags = dlgSetSize->windowFlags();
    dlgSetSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dlgSetSize->setRowColumn(theModel->rowCount(), theModel->columnCount());

    int ret = dlgSetSize->exec();
    if(ret == QDialog::Accepted){
        theModel->setRowCount(dlgSetSize->rowCount());
        theModel->setColumnCount(dlgSetSize->columnCount());
    }

    delete dlgSetSize;
}

void MainWindow::on_actTab_SetHeader_triggered()
{
    if(dlgSetHeaders == NULL)
        dlgSetHeaders = new QWDialogHeaders(this);

    if(theModel->columnCount() != dlgSetHeaders->headerList().count()){
        //如果表头列数变化，重新初始化
        QStringList headList;
        for(int i=0; i < theModel->columnCount(); ++i)
            headList.append(theModel->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        dlgSetHeaders->setHeaderList(headList);
    }

    int res = dlgSetHeaders->exec(); //以模态的方式显示
    if(res == QDialog::Accepted){
        QStringList headList = dlgSetHeaders->headerList();
        theModel->setHorizontalHeaderLabels(headList);
    }
}


















