#include "qmyvideowidget.h"
#include <QKeyEvent>
#include <QMouseEvent>

QmyVideoWidget::QmyVideoWidget(QWidget *parent):QVideoWidget(parent)
{

}

//按键事件，ESC退出全屏
void QmyVideoWidget::keyPressEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Escape) && isFullScreen()){
        setFullScreen(false);
        event->accept();
        QWidget::keyPressEvent(event);
    }
    QWidget::keyPressEvent(event);
}

//鼠标事件，单击控制暂停和继续播放
void QmyVideoWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(thePlayer->state() == QMediaPlayer::PlayingState)
            thePlayer->pause();
        else
            thePlayer->play();
    }
    QWidget::mousePressEvent(event);
}

//设置播放器
void QmyVideoWidget::setMediaPlayer(QMediaPlayer *player)
{
    thePlayer = player;
}
