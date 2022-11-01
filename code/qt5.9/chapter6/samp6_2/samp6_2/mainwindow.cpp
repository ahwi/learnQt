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

void MainWindow::setACellText(int row, int column, QString text)
{
    QModelIndex index = theModel->index(row, column);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(index, QItemSelectionModel::Select);
    theModel->setData(index, text, Qt::DisplayRole);
}

void MainWindow::setActLocateEnable(bool enable)
{
    ui->actTab_Locate->setEnabled(enable);
}


void MainWindow::setDlgLocateNull()
{
    dlgLocate = NULL;
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

// 创建StayOnTop的对话框，对话框关闭时自动删除
void MainWindow::on_actTab_Locate_triggered()
{
    // 通过控制actTab_Locate的enable来避免重复点击
    ui->actTab_Locate->setEnabled(false);

    dlgLocate = new QWDialogLocate(this);
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose); //对话框关闭时自动删除对话框，用于不需要读取返回值的对话框
    Qt::WindowFlags flags = dlgLocate->windowFlags();
    dlgLocate->setWindowFlags(flags | Qt::WindowStaysOnTopHint); //设置对话框StaysOnTop

    dlgLocate->setSpinRange(theModel->rowCount(), theModel->columnCount());
    QModelIndex curIndex = theSelection->currentIndex();
    if(curIndex.isValid())
        dlgLocate->setSpinValue(curIndex.row(), curIndex.column());

    dlgLocate->show();	//非模态显示对话框
}

















