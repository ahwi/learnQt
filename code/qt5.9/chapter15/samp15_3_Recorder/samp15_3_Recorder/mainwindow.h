#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioRecorder>
#include <QAudioProbe>

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
    void onStateChanged(QMediaRecorder::State state);


private:
    QAudioRecorder *recorder; 	//音频录音
    QAudioProbe *probe;			//探测器

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
