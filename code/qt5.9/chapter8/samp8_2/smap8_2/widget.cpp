#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QtMath>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setPalette(QPalette(Qt::white)); // 设置窗口背景色
    setAutoFillBackground(true);
    resize(600, 300); // 固定初始化窗口大小
}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);	//创建painter对象

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    //生成五角星的5个顶点，假设原点在五角星中心
    qreal r = 100;	// 半径
    const qreal Pi = 3.14159;
    qreal deg = Pi*72/180;	// 角度转成弧度：将72度转成弧度

    QPoint points[5] = {
        QPoint(r, 0),
        QPoint(r*qCos(deg), -r*qSin(deg)),
        QPoint(r*qCos(2*deg), -r*qSin(2*deg)),
        QPoint(r*qCos(3*deg), -r*qSin(3*deg)),
        QPoint(r*qCos(4*deg), -r*qSin(4*deg)),
    };

    // 设置字体
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);

    // 设置画笔
    QPen penLine;
    penLine.setWidth(2); // 线宽
    penLine.setColor(Qt::blue);	// 划线颜色
    penLine.setStyle(Qt::SolidLine); // 线的类型
    penLine.setCapStyle(Qt::FlatCap); // 线端点样式
    penLine.setJoinStyle(Qt::BevelJoin); // 线的连接点样式
    painter.setPen(penLine);

    // 设置画刷
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern); // 画刷填充样式
    painter.setBrush(brush);

    // 设计绘制五角星的PainterPath，以便重复使用
    QPainterPath starPath;
    starPath.moveTo(points[0]);
    starPath.lineTo(points[2]);
    starPath.lineTo(points[4]);
    starPath.lineTo(points[1]);
    starPath.lineTo(points[3]);
    starPath.closeSubpath();	// 闭合路径，最后一个点与第一个点相连

    starPath.addText(points[0], font, "0");
    starPath.addText(points[1], font, "1");
    starPath.addText(points[2], font, "2");
    starPath.addText(points[3], font, "3");
    starPath.addText(points[4], font, "4");

    // 绘图
    painter.save();	// 保存坐标状态
    painter.translate(100, 120); // 平移
    painter.drawPath(starPath); // 画星星
    painter.drawText(0, 0, "S1");

    painter.restore(); // 恢复上一次坐标状态

    painter.translate(300, 120); // 平移
    painter.scale(0.8, 0.8); // 缩放
    painter.rotate(90); // 顺时针旋转
    painter.drawPath(starPath); // 画星星
    painter.drawText(0, 0, "S2");

    painter.resetTransform(); // 复位所有坐标变换
    painter.translate(500, 120); // 平移
    painter.rotate(-145); // 逆时针旋转
    painter.drawPath(starPath); // 画星星
    painter.drawText(0, 0, "S3");
}
















