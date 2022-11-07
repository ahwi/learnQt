#include "qdlglogin.h"
#include "ui_qdlglogin.h"
#include <QCryptographicHash>
#include <QSettings>

QDlgLogin::QDlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDlgLogin)
{
    ui->setupUi(this);

    ui->editPSWD->setEchoMode(QLineEdit::Password);	//设置密码的显示模式
    this->setAttribute(Qt::WA_DeleteOnClose);	//设置关闭时删除
    this->setWindowFlag(Qt::SplashScreen, true);	//设置为SplashScreen,窗口无边框，不在任务栏显示

    readSettings();	//读取设置
}

QDlgLogin::~QDlgLogin()
{
    delete ui;
}

void QDlgLogin::readSettings()
{
    QString organization = "WWB-Qt";	//用于注册表
    QString appName = "samp6_5";	//HKEY_CURRENT_USER/Software/WWB-Qt/samp6_5

    QSettings settings(organization, appName);	//设置
    bool saved = settings.value("saved", false).toBool();	//读取saved键的值
    m_user = settings.value("Username", "user").toString();	//读取Username键的值，缺省为`user`

    QString defaltPswd = encrypt("123456");
    m_pswd = settings.value("PSWD", defaltPswd).toString();	//读取PSWD键的值

    if(saved)
        ui->editUser->setText(m_user);

    ui->chkBoxSave->setChecked(saved);
}

void QDlgLogin::writeSettings()
{

}

// 字符串md5算法加密
QString QDlgLogin::encrypt(const QString &str)
{
    QByteArray array;
    array.append(str);

    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(array);
    QByteArray resultArray = hash.result();
    QString md5 = resultArray.toHex();
    return md5;
}
