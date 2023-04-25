#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->widget->setPowerLevel(ui->slider->value());
    QString str = QStringLiteral("当前电量：") + QString::asprintf("%d %%", ui->slider->value());
    ui->labInfo->setText(str);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_slider_valueChanged(int value)
{
    ui->widget->setPowerLevel(value);
    QString str = QStringLiteral("当前电量：") + QString::asprintf("%d %%", value);
    ui->labInfo->setText(str);
}
