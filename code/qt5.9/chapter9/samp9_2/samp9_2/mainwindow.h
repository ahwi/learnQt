#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE


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
    void on_btnLegendFont_clicked();

    void on_radioSeries0_clicked();

    void on_radioSeries1_clicked();

private:
    QLineSeries *curSeries;	// 当前序列
    QValueAxis *curAxis;	// 当前坐标轴
    void createChart();
    void prepareData();
    void updateFromChart();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
