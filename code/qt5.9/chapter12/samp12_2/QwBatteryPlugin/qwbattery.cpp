#include "qwbattery.h"
#include <QPainter>

QwBattery::QwBattery(QWidget *parent) :
    QWidget(parent)
{
}

void QwBattery::paintEvent(QPaintEvent *event)
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

    brush.setColor(mColorBorder);
    painter.setBrush(brush);
    rect.setRect(110, 15, 10, 20);
    painter.drawRect(rect);	//画电池正极头

    //画电池柱
    if(mPowerLevel > mWarnLevel){ //正常颜色电量柱
        brush.setColor(mColorPower);
        pen.setColor(mColorPower);
    } else { //电量低电量柱
        brush.setColor(mColorWarning);
        pen.setColor(mColorWarning);
    }
    painter.setBrush(brush);
    painter.setPen(pen);
    if(mPowerLevel > 0){
        rect.setRect(5, 5, mPowerLevel, 40);
        painter.drawRect(rect);
    }

    //绘制电量百分比文字
    QFontMetrics textSize(this->font());
    QString powStr = QString::asprintf("%d%%", mPowerLevel);
    QRect textRect = textSize.boundingRect(powStr); //得到字符串的str
    painter.setFont(this->font());
    pen.setColor(mColorBorder);
    painter.setPen(pen);
    painter.drawText(55-textRect.width()/2, 23+textRect.height()/2, powStr);
}

void QwBattery::setPowerLevel(int pow)
{
    //设置当前电量值
    mPowerLevel = pow;
    emit powerLevelChanged(pow); // 发射信号
    repaint();
}

int QwBattery::powerLevel()
{
    //返回当前电量值
    return mPowerLevel;
}

void QwBattery::setWarnLevel(int warn)
{
    //设置电量低阈值
    mWarnLevel = warn;
    repaint();
}

int QwBattery::warnLevel()
{
    //返回电量低阈值
    return mWarnLevel;
}


QSize QwBattery::sizeHint()
{
    // 缺省大小，调整比例
    int h = this->height();
    int w = h*12/5;
    QSize size(w, h);
    return size;
}
