#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer();
    playlist = new QMediaPlaylist();
    playlist->setPlaybackMode(QMediaPlaylist::Loop); //设置循环播放模式
    player->setPlaylist(playlist);

    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(playStateChanged(QMediaPlayer::State)));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(onDurationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
    connect(playlist, SIGNAL(currentIndexChanged(int)), this, SLOT(onPlaylistChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//添加文件
void MainWindow::on_btnAdd_clicked()
{
    QString curPath = QDir::currentPath();
    QString title = "Select Audio File";
    QString filter = "音频文件(*.mp3 *.wav *.wma);;mp3文件(*.mp3);;wav文件(*.wav);;wma文件(*.wma);;所有文件(*.*)"; //文件过滤器

    QStringList filenames = QFileDialog::getOpenFileNames(this, title, curPath, filter);
    for(int i=0;i < filenames.count(); i++){
        QString filename = filenames.at(i);
        playlist->addMedia(QUrl::fromLocalFile(filename)); //添加文件

        QFileInfo fileInfo(filename);
        ui->listWidget->addItem(fileInfo.fileName()); //添加到界面文件夹列表
    }

    if(player->state() != QMediaPlayer::PlayingState)
        playlist->setCurrentIndex(0);
    player->play();
}

//播放列表改变时，更新当前播放文件名的显示
void MainWindow::onPlaylistChanged(int position)
{
    ui->listWidget->setCurrentRow(position);
    QListWidgetItem *item = ui->listWidget->currentItem();
    ui->labCurrentMedia->setText(item->text());
}

//文件时长变化时，更新进度显示
void MainWindow::onDurationChanged(qint64 duration)
{
    ui->sliderPosition->setMaximum(duration);

    int sec = duration/1000; //秒
    int min = sec/60; //分钟
    sec = sec % 60; //余数秒
    durationTime = QString::asprintf("%d:%d", min, sec);
    ui->labRatio->setText(postionTime + "/" + durationTime);
}

//当前文件播放位置发生变化，更新进度显示
void MainWindow::onPositionChanged(qint64 position)
{
    if(ui->sliderPosition->isSliderDown())
        return;

    ui->sliderPosition->setSliderPosition(position);

    int sec = position/1000; //秒
    int min = sec/60; //分钟
    sec = sec % 60; //余数秒
    durationTime = QString::asprintf("%d:%d", min, sec);
    ui->labRatio->setText(postionTime + "/" + durationTime);
}

//播放状态改变时，切换按钮状态
void MainWindow::playStateChanged(QMediaPlayer::State state)
{
    ui->btnPlay->setEnabled(!(state == QMediaPlayer::PlayingState));
    ui->btnPause->setEnabled(state == QMediaPlayer::PlayingState);
    ui->btnStop->setEnabled(state == QMediaPlayer::PlayingState);
}

//播放
void MainWindow::on_btnPlay_clicked()
{
    if(playlist->currentIndex() < 0)
        playlist->setCurrentIndex(0);
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

//双击时，切换播放文件
void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    int idx = index.row();
    playlist->setCurrentIndex(idx);
    player->play();
}

//清空列表
void MainWindow::on_btnClear_clicked()
{
    player->stop();
    playlist->clear();
    ui->listWidget->clear();
}

//调整音量
void MainWindow::on_sliderVolumn_valueChanged(int value)
{
    player->setVolume(value);
}

//静音控制
void MainWindow::on_btnSound_clicked()
{
    bool muted = player->isMuted();
    player->setMuted(!muted);
    if(muted)
        ui->btnSound->setIcon(QIcon(":/images/images/volumn.bmp"));
    else
        ui->btnSound->setIcon(QIcon(":/images/images/mute.bmp"));
}

//文件进度调控
void MainWindow::on_sliderPosition_valueChanged(int value)
{
    player->setPosition(value);
}

//前一文件
void MainWindow::on_btnPrevious_clicked()
{
    playlist->previous();
}

//下一文件
void MainWindow::on_btnNext_clicked()
{
    playlist->next();
}

//移除一个文件
void MainWindow::on_btnRemove_clicked()
{
    int pos = ui->listWidget->currentRow();
    // 从QListWidget中删除
    QListWidgetItem *item = ui->listWidget->takeItem(pos);
    delete item;

    if(playlist->currentIndex() == pos){ //是当前播放的曲目
        int nextPos = 0;
        if(pos>=1)
            nextPos = pos -1;
        playlist->removeMedia(pos); //从播放列表里面删除
        if(ui->listWidget->count() > 0){
            playlist->setCurrentIndex(nextPos);
            onPlaylistChanged(nextPos);
        }else{
            player->stop();
            ui->labCurrentMedia->setText("无曲目");
        }
    } else{
        playlist->removeMedia(pos);
    }
}
