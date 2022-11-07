#ifndef QDLGLOGIN_H
#define QDLGLOGIN_H

#include <QDialog>

namespace Ui {
class QDlgLogin;
}

class QDlgLogin : public QDialog
{
    Q_OBJECT

public:
    explicit QDlgLogin(QWidget *parent = nullptr);
    ~QDlgLogin();

private:
    void readSettings();	//读取设置, 从注册表
    void writeSettings();	//写入设置，从注册表

    QString encrypt(const QString &str); //加密字符串;md5算法加密

private:
    bool m_moveing=false;	//表示窗口是否在鼠标的操作下移动
    QPoint m_lastPos;	//上一次鼠标的位置
    QString m_user;
    QString m_pswd;

private:
    Ui::QDlgLogin *ui;
};

#endif // QDLGLOGIN_H
