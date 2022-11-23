#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labViewCord = new QLabel("View 坐标");
    labViewCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labViewCord);

    labSceneCord = new QLabel("Scene 坐标");
    labSceneCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labSceneCord);

    labItemCord = new QLabel("Item 坐标");
    labItemCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labItemCord);

    ui->view->setCursor(Qt::CrossCursor);
    ui->view->setMouseTracking(true);
    ui->view->setDragMode(QGraphicsView::RubberBandDrag);

    // TODO: connect

    initGraphicsSystem();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initGraphicsSystem()
{

}
