#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractSocket>
#include <QHostInfo>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpClient = new QTcpSocket(this); //创建socket变量
    labSocketState = new QLabel("Socket 状态："); //状态栏标签
    labSocketState->setMinimumWidth(250);
    ui->statusbar->addWidget(labSocketState);
    QString localIP = getLocalIP();	//本机IP
    this->setWindowTitle(this->windowTitle() + "----本机IP：" + localIP);
    ui->comboServer->addItem(localIP);

    connect(tcpClient, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(tcpClient, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(tcpClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//获取本机IP地址
QString MainWindow::getLocalIP()
{
    QString hostName = QHostInfo::localHostName();	//本地主机名
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString localIP = "";
    QList<QHostAddress> addList = hostInfo.addresses();

    for(int i=0; i<addList.count(); i++){
        QHostAddress aHost = addList.at(i);
        if(QAbstractSocket::IPv4Protocol == aHost.protocol()){
            localIP = aHost.toString();
            break;
        }
    }
    return localIP;
}

//connected()信号槽函数
void MainWindow::onConnected()
{
    ui->plainTextEdit->appendPlainText("**已连接到服务器");
    ui->plainTextEdit->appendPlainText("**peer address:" +
                             tcpClient->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**peer port:" +
                             QString::number(tcpClient->peerPort()));
    ui->actConnect->setEnabled(false);
    ui->actDisconnect->setEnabled(true);
}

//disConnected()信号槽函数
void MainWindow::onDisconneted()
{
    ui->plainTextEdit->appendPlainText("**已断开与服务器的连接");
    ui->actConnect->setEnabled(true);
    ui->actDisconnect->setEnabled(false);
}

//socket 状态变化时
void MainWindow::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    switch (socketState) {
    case QAbstractSocket::UnconnectedState:
        labSocketState->setText("socket 状态：UnconnectedState"); break;
    case QAbstractSocket::HostLookupState:
        labSocketState->setText("socket 状态：HostLookupState"); break;
    case QAbstractSocket::ConnectingState:
        labSocketState->setText("socket 状态：ConnectingState"); break;
    case QAbstractSocket::ConnectedState:
        labSocketState->setText("socket 状态：ConnectedState"); break;
    case QAbstractSocket::BoundState:
        labSocketState->setText("socket 状态：BoundState"); break;
    case QAbstractSocket::ListeningState:
        labSocketState->setText("socket 状态：ListeningState"); break;
    case QAbstractSocket::ClosingState:
        labSocketState->setText("socket 状态：ClosingState");
    }
}

//读取socket传入的数据
void MainWindow::onSocketReadyRead()
{
    while (tcpClient->canReadLine()) {
        ui->plainTextEdit->appendPlainText("[in] " + tcpClient->readLine());
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{

}

//“连接到服务器”按钮
void MainWindow::on_actConnect_triggered()
{
    QString addr = ui->comboServer->currentText();
    quint16 port = ui->spinPort->value();
    tcpClient->connectToHost(addr, port);
}

//“端口连接”按钮
void MainWindow::on_actDisconnect_triggered()
{
    if(tcpClient->state() == QAbstractSocket::ConnectedState)
        tcpClient->disconnectFromHost();
}

//发送数据
void MainWindow::on_btnSend_clicked()
{
    QString msg = ui->editMsg->text();
    ui->plainTextEdit->appendPlainText("[out] " + msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();

    QByteArray str = msg.toUtf8();
    str.append('\n'); //添加一个换行符
    tcpClient->write(str);
}
