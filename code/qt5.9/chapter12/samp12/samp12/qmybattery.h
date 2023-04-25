#ifndef QMYBATTERY_H
#define QMYBATTERY_H

#include <QWidget>

class QmyBattery : public QWidget
{
    Q_OBJECT
public:
    explicit QmyBattery(QWidget *parent = nullptr);

signals:

public:
//    void setPowerLevel(int pow);	//设置当前电量
//    int powerLevel();
//    void setWarnLevel();			//设置电量低阈值
//    int warnLevel();
//    QSize sizeHint();				//缺省大小

protected:
    void paintEvent(QPaintEvent *event);

private:
    QColor mColorBack = Qt::white;		//背景颜色
    QColor mColorBorder = Qt::black;	//电池边框颜色
    QColor mColorPower = Qt::green;		//电量柱颜色
    QColor mColorWarning = Qt::red;		//电量短缺时的颜色
    int mPowerLevel = 60;				//电量0-100
    int mWarnLevel = 20;				//电量低警示阈值

};

#endif // QMYBATTERY_H
