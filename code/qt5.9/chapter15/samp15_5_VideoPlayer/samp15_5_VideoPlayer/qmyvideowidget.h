#ifndef QMYVIDEOWIDGET_H
#define QMYVIDEOWIDGET_H

#include <QVideoWidget>
#include <QMediaPlayer>


class QmyVideoWidget : public QVideoWidget
{
public:
    QmyVideoWidget(QWidget *parent = Q_NULLPTR);

public:
    void setMediaPlayer(QMediaPlayer *player);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QMediaPlayer *thePlayer;
};

#endif // QMYVIDEOWIDGET_H
