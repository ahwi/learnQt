#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStateChanged(QMediaPlayer::State state);
    void onDurationChanged(qint64 duration);
    void onPostionChanged(qint64 postion);

    void on_btnAdd_clicked();

    void on_btnPlay_clicked();

    void on_btnPause_clicked();

    void on_btnStop_clicked();

    void on_sliderPosition_valueChanged(int value);

    void on_sliderVolumn_valueChanged(int value);

    void on_btnSound_clicked();

    void on_btnFullScreen_clicked();

private:
    QMediaPlayer *player; //视频播放器

    QString durationTime;
    QString postionTime;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
