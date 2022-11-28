#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}


// 创建图表
void MainWindow::createChart()
{
    QChartView *chartView = new QChartView(this);	// 创建QChartView

    QChart *chart = new QChart();	//创建QChart
    chart->setTitle("简单函数曲线");

    chartView->setChart(chart);	//Chart添加到ChartView
    this->setCentralWidget(chartView);

    // 创建曲线序列
    QLineSeries *series0 = new QLineSeries();
    QLineSeries *series1 = new QLineSeries();
    series0->setName("Sin曲线");
    series1->setName("Cos曲线");
    chart->addSeries(series0);	//序列添加到图表中
    chart->addSeries(series1);

}
