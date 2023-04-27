#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnGetHostInfo_clicked()
{
    // QHostInfo获取主机信息
//    ui->plainTextEdit->clear();

    QString hostName = QHostInfo::localHostName();	//本地主机名
    ui->plainTextEdit->appendPlainText("本地主机名：" + hostName + "\n");

    QHostInfo hostInfo = QHostInfo::fromName(hostName);

    QList<QHostAddress> addList = hostInfo.addresses();	// IP地址列表
    for(int i=0;i<addList.count(); i++){
        QHostAddress aHost = addList.at(i);	//每一项是一个QHostAddress
        bool show = ui->chkOnlyIPv4->isChecked();	//是否只显示IPv4
        if(show)
            show = (QAbstractSocket::IPv4Protocol == aHost.protocol()); //协议类型是否为IPv4
        else
            show = true;
        if(show){
            ui->plainTextEdit->appendPlainText("协议：" + protocolName(aHost.protocol())); //协议类型
            ui->plainTextEdit->appendPlainText("本机IP地址：" + aHost.toString()); //IP地址
            ui->plainTextEdit->appendPlainText("");
        }
    }

}

QString Dialog::protocolName(QAbstractSocket::NetworkLayerProtocol protocol)
{
    switch (protocol) {
        case QAbstractSocket::IPv4Protocol:
            return "IPv4 Protocol";
        case QAbstractSocket::IPv6Protocol:
            return "IPv6 Protocol";
        case QAbstractSocket::AnyIPProtocol:
            return "Any IP Protocol";
        default:
            return "Unknow Network Layer Protocol";
    }
}
