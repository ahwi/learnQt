#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

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

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    int w = width();
    int h = height();
    int side = qMin(w, h); // 取长和宽的小值

    QRect rect((w-side)/2, (h-side)/2, side, side);  // viewport 矩形区
    painter.drawRect(rect);  // viewport大小

    painter.setViewport(rect);	// 设置 viewport
    painter.setWindow(-100, -100, 200, 200);  // 设置窗口大小，逻辑坐标

    // 设置画笔
    QPen pen;
    pen.setWidth(1); // 线宽
    pen.setColor(Qt::red); // 划线颜色
    pen.setStyle(Qt::SolidLine); // 线的类型
    pen.setCapStyle(Qt::FlatCap); // 线端点样式
    pen.setJoinStyle(Qt::BevelJoin); // 线的连接点样式
    painter.setPen(pen);

    // 线性渐变
    QLinearGradient linearGrad(0, 0, 100, 0); // 从左到右
    linearGrad.setColorAt(0, Qt::yellow); // 起点颜色
    linearGrad.setColorAt(1, Qt::green); // 终点颜色
    linearGrad.setSpread(QGradient::PadSpread);  // 扩展方式
    painter.setBrush(linearGrad);

    painter.drawEllipse(QPoint(50, 0), 50, 50);
}
