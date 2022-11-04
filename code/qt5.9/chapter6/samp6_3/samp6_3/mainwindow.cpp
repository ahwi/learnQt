#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qformdoc.h"
#include "qformtable.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();	//清除所有页面
    ui->tabWidget->setTabsClosable(true);	//设置Page有关闭按钮，关闭按钮点击时只发送信号

    this->setCentralWidget(ui->tabWidget);
    this->setWindowState(Qt::WindowMaximized);	//窗口最大化显示
    this->setAutoFillBackground(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//绘制窗口背景图片
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0, ui->mainToolBar->height(),
                       this->width(), this->height()-ui->mainToolBar->height(),
                       QPixmap(":/images/images/back2.jpg"));

}

// 创建QFormDoc窗口,并在tabWidget窗口显示
void MainWindow::on_actWidgetInsite_triggered()
{
    QFormDoc *formDoc = new QFormDoc(this);

    formDoc->setAttribute(Qt::WA_DeleteOnClose);    // 关闭时自动删除

    int cur = ui->tabWidget->addTab(formDoc, QString::asprintf("Doc %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


// 创建QFormDoc窗口并以独立子窗口的形式显示
void MainWindow::on_actWidget_triggered()
{
    QFormDoc *formDoc = new QFormDoc();	//不指定父窗口，用show方式显示
    formDoc->setAttribute(Qt::WA_DeleteOnClose);	//设置关闭时删除
    formDoc->setWindowTitle("基于QWidget的窗体，无父窗口，关闭时删除");

//    formDoc->setWindowFlag(Qt::Window, true);	//如果指定了父窗口，子窗口需设置Qt::Window配置，
                                                //子窗口才能以独立的方式存在; QMainWindow的子类没有这种情况
    formDoc->setWindowOpacity(0.9);	//不透明度
    formDoc->show();
}

// 创建QFormTable窗口并在tabWidget窗口显示
void MainWindow::on_actWindowInsite_triggered()
{
    QFormTable *formTable = new QFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);	//关闭时删除

    int curIndex = ui->tabWidget->addTab(formTable, QString::asprintf("Doc %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(curIndex);
    ui->tabWidget->setVisible(true);
}

// 创建QFormTable窗口并以独立的子窗口显示
void MainWindow::on_actWindow_triggered()
{
    QFormTable *formTable = new QFormTable(this);
//    QFormTable *formTable = new QFormTable();
    formTable->setAttribute(Qt::WA_DeleteOnClose);	//设置关闭时删除
    formTable->setWindowTitle("基于QMainWindow的窗口，指定父窗口，关闭时删除");

    formTable->show();
}

// 关闭标签页
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if(index < 0)
        return;

    QWidget *aForm = ui->tabWidget->widget(index);
    aForm->close();
}


// 标签页变化的槽函数，添加对无标签也的处理
void MainWindow::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);

    bool visuable = ui->tabWidget->count() > 0;
    ui->tabWidget->setVisible(visuable);
}
