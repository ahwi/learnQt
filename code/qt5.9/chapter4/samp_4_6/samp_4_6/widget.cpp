#include "widget.h"
#include "ui_widget.h"
#include <QTextBlock>
#include <QMenu>

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


void Widget::on_btnIniItems_clicked()
{
    //初始化列表
    QIcon icon;
    icon.addFile(":/images/icons/aim.ico");
    ui->comboBox->clear();
    for(int i=0; i < 20; i++)
    {
        ui->comboBox->addItem(icon, QString::asprintf("Item %d", i));	//带图标
//        ui->comboBox->addItem(QString::asprintf("Item %d", i));	//不带图标
    }

}

void Widget::on_pushButton_3_clicked()
{
    // 使用addItems()添加一个字符串列表项
//    ui->comboBox_2->clear();
//    QStringList strList;
//    strList << "北京" << "上海" << "天津" << "河北省" << "山东省" << "山西省";
//    ui->comboBox_2->addItems(strList);

    // 初始化具有自定义数据的ComboBox
    QMap<QString, int> cityZone;
    cityZone.insert("北京", 10);
    cityZone.insert("上海", 21);
    cityZone.insert("天津", 22);
    cityZone.insert("大连", 411);
    cityZone.insert("锦州", 416);
    cityZone.insert("徐州", 516);
    cityZone.insert("福州", 591);
    cityZone.insert("青岛", 532);
    ui->comboBox_2->clear();
    foreach(const QString str, cityZone.keys())
        ui->comboBox_2->addItem(str, cityZone.value(str));
}

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->plainTextEdit->appendPlainText(arg1);
}

void Widget::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    QString zone = ui->comboBox_2->currentData().toString();	//项关联的数据
    ui->plainTextEdit->appendPlainText(arg1+":区号="+zone);
}

void Widget::on_btnToComboBox_clicked()
{
    //plainTextEdit的内容逐行添加为comboBox的项
    QTextDocument* doc = ui->plainTextEdit->document();	//文本对象
    int cnt=doc->blockCount();	//回车符是一个block
    QIcon icon(":/images/icons/aim.ico");
    ui->comboBox->clear();
    for(int i=0; i<cnt; ++i)
    {
        QTextBlock textLine = doc->findBlockByNumber(i);	//文本中的一段
        QString str = textLine.text();
        ui->comboBox->addItem(icon, str);
    }
}

void Widget::on_plainTextEdit_customContextMenuRequested(const QPoint &pos)
{
    // 创建并弹出标准弹出式菜单
    QMenu *menu = ui->plainTextEdit->createStandardContextMenu();
    menu->exec(pos);
}

void Widget::on_btnClearText_clicked()
{
    ui->plainTextEdit->clear();
}

void Widget::on_chkBoxEditable_clicked(bool checked)
{
    ui->comboBox->setEditable(checked);
}

void Widget::on_chkBoxReadonly_clicked(bool checked)
{
    ui->plainTextEdit->setReadOnly(checked);
}
