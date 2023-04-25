#ifndef QWBATTERY_H
#define QWBATTERY_H

#include <QDesignerExportWidget>
#include <QWidget>

class QDESIGNER_WIDGET_EXPORT QwBattery : public QWidget
{
    Q_OBJECT
    //自定义属性
    Q_PROPERTY(int powerLevel READ powerLevel WRITE setPowerLevel
               NOTIFY powerLevelChanged DESIGNABLE true)
public:
    explicit QwBattery(QWidget *parent = nullptr);

signals:
    void powerLevelChanged(int); // 发射信号

public:
    void setPowerLevel(int pow);	//设置当前电量
    int powerLevel();
    void setWarnLevel(int warn);			//设置电量低阈值
    int warnLevel();
    QSize sizeHint();				//缺省大小

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

#endif // QWBATTERY_H
