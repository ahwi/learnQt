#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractItemView>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    theModel = new QStandardItemModel(2, FixedColumnCount, this);	//数据模型
    theSelection = new QItemSelectionModel(theModel);	//Item选择模型

    // 选择当前单元格变化时的信号与槽
    connect(theSelection, SIGNAL(currentChanged(QModelIndex, QModelIndex)),
            this, SLOT(on_currentChanged(QModelIndex, QModelIndex)));

    ui->tableView->setModel(theModel); // 设置数据模型
    ui->tableView->setSelectionModel(theSelection);	// 设置选择模型
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    // 创建状态栏组件
    LabCurFile = new QLabel("当前文件：", this);
    LabCurFile->setMinimumWidth(200);

    LabCellPos = new QLabel("当前单元格：", this);
    LabCellPos->setMinimumWidth(180);
    LabCellPos->setAlignment(Qt::AlignCenter);

    LabCellText = new QLabel("单元格内容：", this);
    LabCellText->setMinimumWidth(150);

    ui->statusbar->addWidget(LabCurFile);
    ui->statusbar->addWidget(LabCellPos);
    ui->statusbar->addWidget(LabCellText);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::iniModelFromStringList(QStringList & aFileContent)
{
    // 设置模型行数
    int rowCnt = aFileContent.count();
    theModel->setRowCount(rowCnt-1);

    QString head = aFileContent.at(0);
    QStringList headList = head.split(QRegExp("\\s"), Qt::SkipEmptyParts);

    // 设置表头
    theModel->setHorizontalHeaderLabels(headList);


    QString s;
    QStringList tempList;

    QStandardItem *tempItem = NULL;
    for(int row=0; row < rowCnt-1; ++row ){
        s = aFileContent.at(row+1);
        tempList = s.split(QRegExp("\\s"), Qt::SkipEmptyParts);
        for(int column=0; column < FixedColumnCount-1; ++column){
            tempItem = new QStandardItem(tempList.at(column));
            theModel->setItem(row, column, tempItem);
        }

        // 每一行的最后一列
        tempItem = new QStandardItem();
        tempItem->setCheckable(true);
        if(tempList.at(FixedColumnCount -1) == "0")
            ui->actFontBold->setChecked(false);
        else
            ui->actFontBold->setChecked(true);
        theModel->setItem(row, FixedColumnCount-1, tempItem);
    }

}



void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    // 选择单元格变化时的响应
    if(current.isValid())
    {
        LabCellPos->setText(QString::asprintf("当前单元格：%d 行， %d列",
                                              current.row(), current.column()));
        QStandardItem *aItem = theModel->itemFromIndex(current);
        this->LabCellText->setText("单元格内容：" + aItem->text());
        QFont font = aItem->font();
        ui->actFontBold->setChecked(font.bold());
    }
}

void MainWindow::on_actOpen_triggered()
{
    QString curPath = QDir::currentPath();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                             curPath, tr("井数据 (*.txt)"));
    if(fileName.isEmpty())
        return;

    QFile afile(fileName);
    QStringList content;
    if(afile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream aStream(&afile);
        while(!aStream.atEnd()){
            QString line = aStream.readLine();
            ui->plainTextEdit->appendPlainText(line);
            content.append(line);
        }
        iniModelFromStringList(content);

        afile.close();
        this->LabCurFile->setText("当前文件："+fileName);

        ui->actAppend->setEnabled(true);
        ui->actInsert->setEnabled(true);
        ui->actDelete->setEnabled(true);
        ui->actSave->setEnabled(true);
    }
}
























