#include "widget.h"
#include "ui_widget.h"
#include "widget.h"
#include <QPainter>
#include <QBrush>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

// 基本绘图
void Widget::myDrawFilleRect()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);		// 反走样
    painter.setRenderHint(QPainter::TextAntialiasing);	// 抗锯齿

    int w = this->width();
    int h = this->height();
    QRect rect(w/4, h/4, w/2, h/2);	// 要绘制的矩形框

    // 设置画笔
    QPen pen;
    pen.setWidth(3);	//线宽
    pen.setColor(Qt::red);	//线颜色
    pen.setStyle(Qt::SolidLine);	//线的类型，实线或虚线等
    pen.setCapStyle(Qt::FlatCap);	//线的端点样式
    pen.setJoinStyle(Qt::BevelJoin);	//线的连接点样式
    painter.setPen(pen);

    // 设置画刷
    QBrush brush;
    brush.setColor(Qt::yellow);	// 画刷颜色
    brush.setStyle(Qt::SolidPattern);	// 画刷填充样式
    painter.setBrush(brush);

    painter.drawRect(rect);	// 绘制图形
}


/*
* 不明原因会有 QBrush: Incorrect use of TexturePattern 错误，但是不影响显示效果
*/
void Widget::myDrawTextureRect()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);	// 反走样
    painter.setRenderHint(QPainter::TextAntialiasing);	// 抗锯齿

    int w = this->width();
    int h = this->height();
    QRect rect(w/4, h/4, w/2, h/2);	//要绘制的矩形

    QPen pen;
    pen.setWidth(3);	// 线宽
    pen.setColor(Qt::red);	// 线颜色
    pen.setStyle(Qt::SolidLine);		// 线的类型
    pen.setCapStyle(Qt::FlatCap);		// 线的端点样式
    pen.setJoinStyle(Qt::BevelJoin);	// 线的连接点样式
    painter.setPen(pen);

    // 设置画刷
    QPixmap texturePixmap(":images/images/texture.jpg");

    QBrush brush;
    brush.setStyle(Qt::TexturePattern); // 设置填充样式
    brush.setTexture(texturePixmap); // 设置材质图片
    painter.setBrush(brush);

    painter.drawRect(rect);	// 绘制图形
}

void Widget::paintEvent(QPaintEvent *event)
{
//    // 1. 基本绘图1，绘制一个填充矩形
//    myDrawFilleRect();

    // 2. 用材质图片填充一个矩形
    myDrawTextureRect();
}
