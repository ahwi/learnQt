#include "widget.h"
#include "ui_widget.h"
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
    painter.setRenderHint(QPainter::Antialiasing);	//抗锯齿
    painter.setRenderHint(QPainter::TextAntialiasing);

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

void Widget::paintEvent(QPaintEvent *event)
{
    myDrawFilleRect();

}
