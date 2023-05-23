#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this); //创建视频播放器
    player->setNotifyInterval(2000); //信息更新周期
    player->setVideoOutput(ui->videoWidget); //视频显示组件

    ui->videoWidget->setMediaPlayer(player); //设置显示组件的关联播放器


}

MainWindow::~MainWindow()
{
    delete ui;
}


//播放器状态变化
void MainWindow::onStateChanged(QMediaPlayer::State state)
{
    ui->btnAdd->setEnabled(!(state == QMediaPlayer::PlayingState));
    ui->btnPause->setEnabled(state == QMediaPlayer::PlayingState);
    ui->btnStop->setEnabled(state == QMediaPlayer::PlayingState);
}

//文件时长变化时
void MainWindow::onDurationChanged(qint64 duration)
{
    ui->sliderPosition->setMaximum(duration);

    int sec = duration/1000; //秒
    int min = sec/60; //分钟
    sec = sec % 60; //余数秒
    durationTime = QString::asprintf("%d/%d", min, sec);
    ui->labRatio->setText(postionTime+'/'+durationTime);
}

//文件播放位置变化时
void MainWindow::onPostionChanged(qint64 postion)
{
    if(ui->sliderPosition->isSliderDown()) //如果进度条按下时，退出
        return;

    ui->sliderPosition->setValue(postion);

    int sec = postion/1000; //秒
    int min = sec/60; //分钟
    sec = sec % 60; //余数秒
    postionTime = QString::asprintf("%d/%d", min, sec);
    ui->labRatio->setText(postionTime+'/'+durationTime);
}

//打开文件
void MainWindow::on_btnAdd_clicked()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择视频文件";
    QString filter = "mp4文件(*.mp4);;wmv文件(*.wmv);;所有文件(*.*)"; //文件过滤器
    QString aFile = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if(aFile.isEmpty())
        return;

    QFileInfo fileInfo(aFile);
    ui->labCurMedia->setText(fileInfo.fileName());

    player->setMedia(QUrl::fromLocalFile(aFile)); //设置播放文件
    player->play();
}

//播放
void MainWindow::on_btnPlay_clicked()
{
    player->play();
}

//暂停
void MainWindow::on_btnPause_clicked()
{
    player->pause();
}

//停止
void MainWindow::on_btnStop_clicked()
{
    player->stop();
}

//播放位置
void MainWindow::on_sliderPosition_valueChanged(int value)
{
    ui->sliderPosition->setValue(value);
}
//调节音量
void MainWindow::on_sliderVolumn_valueChanged(int value)
{
    player->setVolume(value);
}

//静音按钮
void MainWindow::on_btnSound_clicked()
{
    bool mute = player->isMuted();
    player->setMuted(!mute);
    if(mute)
        ui->btnSound->setIcon(QIcon(":images/images/volumn.bmp"));
    else
        ui->btnSound->setIcon(QIcon(":images/images/mute.bmp"));
}

//全屏按钮
void MainWindow::on_btnFullScreen_clicked()
{
    ui->videoWidget->setFullScreen(true);
}
