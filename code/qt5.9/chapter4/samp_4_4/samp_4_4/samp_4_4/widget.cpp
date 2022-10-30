#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QObject::connect(ui->SliderRed, SIGNAL(valueChanged(int)),
                     this, SLOT(sliderValueChange(int)));
    QObject::connect(ui->SliderGreen, SIGNAL(valueChanged(int)),
                     this, SLOT(sliderValueChange(int)));
    QObject::connect(ui->SliderBlue, SIGNAL(valueChanged(int)),
                     this, SLOT(sliderValueChange(int)));
    QObject::connect(ui->SliderAlpha, SIGNAL(valueChanged(int)),
                     this, SLOT(sliderValueChange(int)));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::sliderValueChange(int value)
{
    // 拖动Red、Green、Blue颜色滚动条时设置textEdit的颜色
    Q_UNUSED(value);
    QColor color;
    int r = ui->SliderRed->value();
    int g = ui->SliderGreen->value();
    int b = ui->SliderBlue->value();
    int alpha = ui->SliderAlpha->value();
    color.setRgb(r, g, b, alpha);

    QPalette pal = ui->textEdit->palette();
    pal.setColor(QPalette::Base, color);

    ui->textEdit->setPalette(pal);
}
