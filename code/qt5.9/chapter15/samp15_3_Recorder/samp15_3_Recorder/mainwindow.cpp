#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    recorder = new QAudioRecorder(this);
    probe = new QAudioProbe;

    probe->setSource(recorder);

    connect(recorder, SIGNAL(stateChanged(QMediaRecorder::State)),
            this, SLOT(onStateChanged(QMediaRecorder::State)));

    if(recorder->defaultAudioInput().isEmpty())
        return;	//无音频输入设备

    foreach(const QString &name, recorder->audioInputs()){
        ui->comboDevices->addItem(name); //音频录入设备列表
    }
    foreach(const QString &name, recorder->supportedAudioCodecs()){
        ui->comboCodec->addItem(name);	//支持的音频编码
    }
    foreach(const int &rate, recorder->supportedAudioSampleRates()){
        ui->comboSampleRate->addItem(QString::number(rate));	//支持的采样率
    }

    //channels
    ui->comboChannels->addItem("1");
    ui->comboChannels->addItem("2");
    ui->comboChannels->addItem("4");

    //quality
    ui->sliderQuality->setRange(0, int(QMultimedia::VeryHighQuality));
    ui->sliderQuality->setValue(int(QMultimedia::NormalQuality));

    //bitrates
    ui->comboBitrate->addItem("32000");
    ui->comboBitrate->addItem("64000");
    ui->comboBitrate->addItem("96000");
    ui->comboBitrate->addItem("1152000");

}

MainWindow::~MainWindow()
{
    delete ui;
}

//录音状态变化
void MainWindow::onStateChanged(QMediaRecorder::State state)
{
    ui->actRecord->setEnabled(state!=QMediaRecorder::RecordingState);
    ui->actPause->setEnabled(state==QMediaRecorder::RecordingState);
    ui->actStop->setEnabled(state==QMediaRecorder::RecordingState);

}
