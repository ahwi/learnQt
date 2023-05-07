#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostInfo>
#include <QHostAddress>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labListen = new QLabel("监听状态：");
    labListen->setMinimumWidth(150);
    ui->statusbar->addWidget(labListen);

    labSocketState = new QLabel("Socket 状态：");
    labSocketState->setMinimumWidth(150);
    ui->statusbar->addWidget(labSocketState);

    QString localIP = getLocalIP();	//本机IP
    this->setWindowTitle(this->windowTitle() + "----本机IP：" + localIP);
    ui->comboIP->addItem(localIP);

    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));


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

//开始监听
void MainWindow::on_actStart_triggered()
{
    QString ip = ui->comboIP->currentText();	//IP地址
    quint16 port = ui->spinPort->value();		//端口
    QHostAddress addr(ip);
    tcpServer->listen(addr, port);	//开始监听
    ui->plainTextEdit->appendPlainText("**开始监听...");
    ui->plainTextEdit->appendPlainText("**服务器地址："
                     + tcpServer->serverAddress().toString());
    ui->plainTextEdit->appendPlainText("**服务器端口l："
                     + QString::number(tcpServer->serverPort()));
    ui->actStart->setEnabled(false);
    ui->actStop->setEnabled(true);
    labListen->setText("监听状态：正在监听");
}

//QTcpServer的newConnection()信号
void MainWindow::onNewConnection()
{
    tcpSocket = tcpServer->nextPendingConnection(); //获取socket
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(onClientConnected()));
    onClientConnected();

    connect(tcpSocket, SIGNAL(disconected()), this, SLOT(onClientDisconnected()));

    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));
    onSocketStateChanged(tcpSocket->state());

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
}

//客户端接入时
void  MainWindow::onClientConnected()
{
    ui->plainTextEdit->appendPlainText("**client socket connected");
    ui->plainTextEdit->appendPlainText("**peer address:" +
                        tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**peer port:" +
                        QString::number(tcpSocket->peerPort()));
}

//客户端断开连接时
void  MainWindow::onClientDisconnected()
{
    ui->plainTextEdit->appendPlainText("**client socket disconnected");
    tcpSocket->deleteLater();
}

//socket 状态变化时
void  MainWindow::onSocketStateChanged(QAbstractSocket::SocketState socketState)
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

//读取缓冲区文本
void  MainWindow::onSocketReadyRead()
{
    while (tcpSocket->canReadLine()) {
        ui->plainTextEdit->appendPlainText("[in] " + tcpSocket->readLine());
    }
}

//停止监听
void MainWindow::on_actStop_triggered()
{
    if(tcpServer->isListening()){ //tcpServer 正在监听
        tcpServer->close(); //停止监听
        ui->actStart->setEnabled(true);
        ui->actStop->setEnabled(false);
        labListen->setText("监听状态：已停止监听");
    }
}

// 发送一行字符串，以换行符结束
void MainWindow::on_btnSend_clicked()
{
    QString msg = ui->editMsg->text();
    ui->plainTextEdit->appendPlainText("[out] " + msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();

    QByteArray str = msg.toUtf8();
    str.append('\n'); //添加一个换行符
    tcpSocket->write(str);
}
