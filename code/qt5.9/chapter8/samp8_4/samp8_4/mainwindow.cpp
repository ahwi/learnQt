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
    QObject::connect(ui->view, SIGNAL(mouseMovePoint(QPoint)), this, SLOT(on_mouseMovePoint(QPoint)));
    QObject::connect(ui->view, SIGNAL(mouseClicked(QPoint)), this, SLOT(on_mouseClicked(QPoint)));

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
    item2->setBrush(QBrush(Qt::blue));
    item2->setFlags(QGraphicsItem::ItemIsSelectable |
                    QGraphicsItem::ItemIsMovable |
                    QGraphicsItem::ItemIsFocusable);
    scene->addItem(item2);

    QGraphicsEllipseItem *item3 = new QGraphicsEllipseItem(-50, -50, 100, 100); // 绘制一个圆形
    item3->setPos(rect.right(), rect.bottom());
    item3->setBrush(QBrush(Qt::red));
    item3->setFlags(QGraphicsItem::ItemIsSelectable |
                    QGraphicsItem::ItemIsMovable |
                    QGraphicsItem::ItemIsFocusable);
    scene->addItem(item3);
}

//窗口大小变化时的事件
void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    ui->labViewSize->setText(QString::asprintf("Graphics View坐标，左上角总是（0,0），宽度=%d，高度=%d",
                                      ui->view->width(), ui->view->height()));
    QRectF rectF = ui->view->sceneRect();	// scene的矩形区
    ui->labSceneRect->setText(QString::asprintf("QGraphicsView::sceneRect=(Left,Top,Width,Height)=%.0f,%.0f,%.0f,%.0f",
                                                rectF.left(), rectF.top(), rectF.width(), rectF.height()));
}


// 鼠标移动事件,point是QGraphicsView的坐标，物理坐标
void MainWindow::on_mouseMovePoint(QPoint point)
{
    labViewCord->setText(QString::asprintf("View 坐标: %d, %d", point.x(), point.y()));
    QPointF pointScene = ui->view->mapToScene(point);	//转换到scene坐标
    labSceneCord->setText(QString::asprintf("Scene 坐标: %.0f, %.0f", pointScene.x(), pointScene.y()));
}

// 鼠标单击事件
void MainWindow::on_mouseClicked(QPoint point)
{
    QPointF pointScene = ui->view->mapToScene(point);	//转换到scene坐标
    QGraphicsItem *item = NULL;
    item = scene->itemAt(pointScene, ui->view->transform());	//获取光标下的绘图项
    if(item != NULL) //有绘图项
    {
        QPointF pointItem = item->mapFromScene(pointScene);	//转换为绘图项的局部坐标
        labItemCord->setText(QString::asprintf("Item 坐标: %.0f,%.0f", pointItem.x(), pointItem.y()));
    }
}




















