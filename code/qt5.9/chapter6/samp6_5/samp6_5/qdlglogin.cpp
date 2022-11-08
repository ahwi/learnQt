#include "qdlglogin.h"
#include "ui_qdlglogin.h"
#include <QCryptographicHash>
#include <QSettings>
#include <QMessageBox>
#include <QMouseEvent>

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
    QString organization = "WWB-Qt";	//用于注册表
    QString appName = "samp6_5";	//HKEY_CURRENT_USER/Software/WWB-Qt/samp6_5
    QSettings settings(organization, appName);	//设置
    settings.setValue("Username", m_user);
    settings.setValue("PSWD", m_pswd);
    settings.setValue("saved", ui->chkBoxSave->isChecked());
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

// "确定"按钮的槽函数
void QDlgLogin::on_btnOK_clicked()
{
    QString usr = ui->editUser->text().trimmed();
    QString pwd = ui->editPSWD->text().trimmed();
    QString encPwd = encrypt(pwd);

    if((usr == m_user) && (encPwd == m_pswd)){
        writeSettings();	//保存设置
        this->accept();
    }else {
        m_tryCount ++;
        if(m_tryCount > 3){
            QMessageBox::critical(this, "错误", "输入错误次数太多，强行退出");
            this->reject();
        }
        else
            QMessageBox::warning(this, "错误提示", "用户名或密码错误");
    }
}

void QDlgLogin::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        m_moveing = true;
        m_lastPos = event->globalPos() - this->pos();
    }
    return QDialog::mousePressEvent(event);
}

void QDlgLogin::mouseMoveEvent(QMouseEvent *event)
{
    if(m_moveing && (event->buttons() & Qt::LeftButton)
            && (event->globalPos()-m_lastPos).manhattanLength() > QApplication::startDragDistance())
    {
        this->move(event->globalPos() - m_lastPos);
        m_lastPos = event->globalPos() - pos();
    }

    return QDialog::mouseMoveEvent(event);
}


void QDlgLogin::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_moveing = false;
//    return;
    return QDialog::mouseReleaseEvent(event);
}
