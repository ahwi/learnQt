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

// 渐变填充
void Widget::myDrawGradient()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 反走样
    painter.setRenderHint(QPainter::TextAntialiasing); // 抗锯齿

    int w = this->width();
    int h = this->height();
    QRect rect(w/4, h/4, w/2, h/2);	// 中间区域矩形框

    // 线性渐变
//    QLinearGradient linearGrad(rect.left(), rect.top(), rect.right(), rect.top()); // 从左到右
//    linearGrad.setColorAt(0, Qt::blue);
//    linearGrad.setColorAt(0.5, Qt::green);
//    linearGrad.setColorAt(1, Qt::red);
////    linearGrad.setSpread(QGradient::PadSpread);	//延展方式
////    linearGrad.setSpread(QGradient::RepeatSpread);
//    linearGrad.setSpread(QGradient::ReflectSpread);
//    painter.setBrush(linearGrad);

    // 径向渐变
//    QRadialGradient radialGrad(w/2, h/2, qMax(w/8, h/8), w/2, h/2);
//    radialGrad.setColorAt(0, Qt::green);
//    radialGrad.setColorAt(1, Qt::blue);
////    radialGrad.setSpread(QGradient::PadSpread);	//延展方式
////    radialGrad.setSpread(QGradient::RepeatSpread);
//    radialGrad.setSpread(QGradient::ReflectSpread);
//    painter.setBrush(radialGrad);

    // 圆锥形渐变
    QConicalGradient coniGrad(w/2, h/2, 45);
    coniGrad.setColorAt(0, Qt::yellow);
    coniGrad.setColorAt(0.5, Qt::blue);
    coniGrad.setColorAt(1, Qt::green);
//    coniGrad.setSpread(QGradient::PadSpread);	// 对于锥形渐变不起作用
    painter.setBrush(coniGrad);

//    painter.drawRect(rect);
    painter.drawRect(this->rect());

}

void Widget::paintEvent(QPaintEvent *event)
{
//    // 1. 基本绘图1，绘制一个填充矩形
//    myDrawFilleRect();

    // 2. 用材质图片填充一个矩形
//    myDrawTextureRect();

    // 3. 渐变填充
    myDrawGradient();
}
