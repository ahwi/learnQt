#ifndef QMYBATTERY_H
#define QMYBATTERY_H

#include <QWidget>

class QmyBattery : public QWidget
{
    Q_OBJECT
public:
    explicit QmyBattery(QWidget *parent = nullptr);

signals:

private:
    QColor mColorBack = Qt::white;		//背景颜色
    QColor mColorBorder = Qt::black;	//电池边框颜色
    QColor mColorPower = Qt::green;		//电量柱颜色
    QColor mColorWarning = Qt::red;		//电量短缺时的颜色
    int mPwoerLevel = 60;				//电量0-100
    int mWarnLevel = 20;				//电量低警示阈值

};

#endif // QMYBATTERY_H
