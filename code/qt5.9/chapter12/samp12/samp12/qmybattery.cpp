#include "qmybattery.h"
#include <QPainter>


QmyBattery::QmyBattery(QWidget *parent) : QWidget(parent)
{

}

void QmyBattery::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // 界面组建的绘制
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    QRect rect(0, 0, width(), height());
    painter.setViewport(rect);
    painter.setWindow(0, 0, 120, 150); //设置窗口大小，逻辑坐标

    // 绘制电池边框
    QPen pen; //设置画笔
    pen.setWidth(2);
    pen.setColor(mColorBorder);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);

    QBrush brush; //设置画刷
    brush.setColor(mColorBack);
    brush.setStyle(Qt::SolidPattern);
    rect.setRect(1, 1, 109, 48);
    painter.drawRect(rect); //绘制电池边框

}

void setPowerLevel(int pow)
{

}
