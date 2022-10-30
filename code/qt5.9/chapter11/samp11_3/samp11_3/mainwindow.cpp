#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actOpenDB_triggered()
{
    QString aFile = QFileDialog::getOpenFileName(this, "打开数据库", "",
                                                 "SQL Lite数据库文件(*.db *.db3)");
    if(aFile.isEmpty())
        return;
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(aFile);
    if(!DB.open()){
        QMessageBox::warning(this, "数据库", "打开数据库失败,失败信息:\n",
                                 QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }

    openTable();

}

// 打开数据库
void MainWindow::openTable()
{
    qryModel = new QSqlQueryModel(this);
    theSelection = new QItemSelectionModel(qryModel);
    qryModel->setQuery("SELECT empNo, Name, Gender, Height, Birthday, Mobile, Province, City, Department, "
                       " Education, Salary FROM employee order by empNo");
    if(qryModel->lastError().isValid()){
        QMessageBox::information(this, "错误", "数据包查询错误，错误信息\n" + qryModel->lastError().text(),
                                 QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }

    qryModel->setHeaderData(0, Qt::Horizontal, "工号");
    qryModel->setHeaderData(1, Qt::Horizontal, "姓名");
    qryModel->setHeaderData(2, Qt::Horizontal, "性别");
    qryModel->setHeaderData(3, Qt::Horizontal, "身高");
    qryModel->setHeaderData(4, Qt::Horizontal, "出生日期");
    qryModel->setHeaderData(5, Qt::Horizontal, "手机");
    qryModel->setHeaderData(6, Qt::Horizontal, "省份");
    qryModel->setHeaderData(7, Qt::Horizontal, "城市");
    qryModel->setHeaderData(8, Qt::Horizontal, "部门");
    qryModel->setHeaderData(9, Qt::Horizontal, "学历");
    qryModel->setHeaderData(10, Qt::Horizontal, "工资");

    ui->tableView->setModel(qryModel);
    ui->tableView->setSelectionModel(theSelection);

    ui->actOpenDB->setEnabled(false);

    ui->actRecEdit->setEnabled(true);
    ui->actRecInsert->setEnabled(true);
    ui->actRecDelete->setEnabled(true);
}

// 更新一条记录
void MainWindow::updateRecord(int recNo)
{
//    WDialogData wdialog(this);
//    wdialog.exec();

    QSqlRecord curRec = qryModel->record(recNo);
    int empNo = curRec.value("EmpNo").toInt();
    QSqlQuery query;	//查询当前记录的所有字段
    query.prepare("select * from employee where EmpNo = :ID");
    query.bindValue(":ID", empNo);
    query.exec();
    query.first();
    if(!query.isValid()) //是否为有效记录
        return;

    curRec = query.record();	//获取当前记录的数据
    WDialogData *dataDialog = new WDialogData(this);
    Qt::WindowFlags flags = dataDialog->windowFlags();
    dataDialog->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);	//设置对话框固定大小

    dataDialog->setUpdateRecord(curRec);	//调用对话框函数更新数据和界面
    bool ret = dataDialog->exec();
    if(ret == QDialog::Accepted){

    }

}

// 在tableView上双击，编辑当前行
void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    int curRow = index.row();
    updateRecord(curRow);
}
