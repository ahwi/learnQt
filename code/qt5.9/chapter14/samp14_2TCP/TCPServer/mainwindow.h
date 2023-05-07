#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLabel *labListen; 		//状态栏标签
    QLabel *labSocketState; //状态栏标签
    QTcpServer *tcpServer;	//TCP服务器
    QTcpSocket *tcpSocket;	//TCP通信的socket
    QString getLocalIP();	//获取本机IP地址

//自定义槽函数
private slots:
    void onNewConnection();			//QTcpServer的newConnection()信号
    void on_actStart_triggered(); 	//开始监听
    void onClientConnected();
    void onClientDisconnected();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onSocketReadyRead();

    void on_actStop_triggered();

    void on_btnSend_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
