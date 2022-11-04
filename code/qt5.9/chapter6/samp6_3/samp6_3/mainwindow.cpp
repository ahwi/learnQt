#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qformdoc.h"
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

// 创建QFormDoc窗口,并在tabWidget窗口应用
void MainWindow::on_actWidgetInsite_triggered()
{
    QFormDoc *formDoc = new QFormDoc(this);

    formDoc->setAttribute(Qt::WA_DeleteOnClose);    // 关闭时自动删除

    int cur = ui->tabWidget->addTab(formDoc, QString::asprintf("Doc %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


// 创建QFormDoc窗口，以独立子窗口的形式显示
void MainWindow::on_actWidget_triggered()
{
    QFormDoc *formDoc = new QFormDoc();	//不指定父窗口，用show方式显示
    formDoc->setAttribute(Qt::WA_DeleteOnClose);	//设置关闭时删除
    formDoc->setWindowTitle("基于QWidget的窗体，无父窗口，关闭时删除");

//    formDoc->setWindowFlag(Qt::Window, true);	//如果指定了父窗口，子窗口需设置Qt::Window配置，子窗口才能以独立的方式存在
    formDoc->setWindowOpacity(0.9);	//不透明度
    formDoc->show();
}
