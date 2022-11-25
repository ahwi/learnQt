#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>

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


// 构造Graphics View的各项
void MainWindow::initGraphicsSystem()
{
    // 添加一个scene
    QRectF rect(-200, -100, 400, 200);
    scene = new QGraphicsScene(rect);
    ui->view->setScene(scene);

    // 画一个矩形框，大小等于scene
    QGraphicsRectItem *item = new QGraphicsRectItem(rect);
    item->setFlags(QGraphicsItem::ItemIsSelectable |
                   QGraphicsItem::ItemIsFocusable);		//可选、可以有焦点，但是不能移动
    QPen pen;
    pen.setWidth(2);
    item->setPen(pen);
    scene->addItem(item);

    // 一个位于scene中心的椭圆，测试局部坐标
    QGraphicsEllipseItem *item2 = new QGraphicsEllipseItem(-100, -50, 200, 100); //矩形框内场景椭圆,绘图项的局部坐标，左上角（-100， -50），宽200，高100
    item2->setPos(0, 0);	//设置椭圆再场景中的位置，缺省位置为(0,0)
    item2->setFlags(QGraphicsItem::ItemIsSelectable |
                    QGraphicsItem::It);
    scene->addItem(item2);

}
























