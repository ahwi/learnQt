#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qformdoc.h"
#include <QMdiSubWindow>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->mdiArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actDoc_New_triggered()
{
    QFormDoc *formDoc = new QFormDoc(this);
    ui->mdiArea->addSubWindow(formDoc);	//文档窗口添加到MDI
    formDoc->show();	//在单独的窗口中显示

    ui->actCut->setEnabled(true);
    ui->actCopy->setEnabled(true);
    ui->actPaste->setEnabled(true);
    ui->actFont->setEnabled(true);
}

void MainWindow::on_actDoc_Open_triggered()
{
    bool needNew = false;	//是否需要新建子窗口
    QFormDoc *formDoc = nullptr;
    if(ui->mdiArea->subWindowList().count() > 0){
        formDoc = (QFormDoc *)ui->mdiArea->activeSubWindow()->widget();	//获取活动的窗口
        needNew = formDoc->isFileOpened();
    }
    else
        needNew = true;

    QString curPath = QDir::currentPath();
    QString filename = QFileDialog::getOpenFileName(this, "打开文件", curPath,
                                "c++程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)");
    if(filename.isEmpty())
        return;
    if(needNew) {
        formDoc = new QFormDoc(this);	// 指定父窗口，必须在父窗口为widget窗口提供一个显示区域
        ui->mdiArea->addSubWindow(formDoc);
    }

    formDoc->loadFromFile(filename);
    formDoc->show();

    ui->actCut->setEnabled(true);
    ui->actCopy->setEnabled(true);
    ui->actPaste->setEnabled(true);
    ui->actFont->setEnabled(true);
}

void MainWindow::on_actViewMode_triggered(bool checked)
{
    if(checked){	//Tab多页显示模式
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);
        ui->mdiArea->setTabsClosable(true);	//页面可关闭
        ui->actCascade->setEnabled(false);
        ui->actTile->setEnabled(false);

    }else{	//子窗口模式
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
        ui->actCascade->setEnabled(true);
        ui->actTile->setEnabled(true);
    }
}

void MainWindow::on_actCascade_triggered()
{
    ui->mdiArea->cascadeSubWindows();
}

void MainWindow::on_actTile_triggered()
{
    ui->mdiArea->tileSubWindows();
}

void MainWindow::on_actCloseALL_triggered()
{
    ui->mdiArea->closeAllSubWindows();
}

