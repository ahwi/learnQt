#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createChart();	// 创建图表
    prepareData();	// 生成数据
    updateFromChart(); // 从图表获得属性值，刷新界面显示
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createChart()
{
    // 创建图表的各个部件
    QChart *chart = new QChart();
    chart->setTitle("简单曲线");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *serials0 = new QLineSeries;
    QLineSeries *serials1 = new QLineSeries;
    serials0->setName("Sin曲线");
    serials1->setName("Cos曲线");
    curSeries = serials0;	// 当前序列

    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setWidth(2);
    pen.setColor(Qt::red);
    serials0->setPen(pen);	// 折线序列的线条设置
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::blue);
    serials1->setPen(pen);	// 折线序列的线条设置
    chart->addSeries(serials0);
    chart->addSeries(serials1);

    QValueAxis *axisX = new QValueAxis;
    curAxis = axisX; // 当前坐标轴
    axisX->setRange(0, 10);
    axisX->setLabelFormat("%.1f");	// 标签格式
    axisX->setTickCount(11);	// 主分隔数
    axisX->setMinorTickCount(4);
    axisX->setTitleText("time(secs)"); // 标题

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-2, 2);
    axisY->setLabelFormat("%.2f");	// 标签格式
    axisY->setTickCount(5);	// 主分隔数
    axisY->setMinorTickCount(4);
    axisY->setTitleText("value"); // 标题

    chart->setAxisX(axisX, serials0);
    chart->setAxisX(axisX, serials1);
    chart->setAxisY(axisY, serials0);
    chart->setAxisY(axisY, serials1);

    // chart->addAxis(axisX, Qt::AlignBottom);	// 坐标轴添加到图表并指定方向
    // chart->addAxis(axisY, Qt::AlignLeft);

    // serials0->attachAxis(axisX);	// 序列serial0附加坐标轴
    // serials0->attachAxis(axisY);

    // serials1->attachAxis(axisX);	// 序列serial1附加坐标轴
    // serials1->attachAxis(axisY);



}


void MainWindow::prepareData()
{
    //为序列生成数据
    QLineSeries *series0=(QLineSeries *)ui->chartView->chart()->series().at(0);
    QLineSeries *series1=(QLineSeries *)ui->chartView->chart()->series().at(1);

    series0->clear(); //清除数据
    series1->clear();

    qsrand(QTime::currentTime().second());//随机数初始化
    qreal   t=0,y1,y2,intv=0.1;
    qreal   rd;
    int cnt=100;
    for(int i=0;i<cnt;i++)
    {
        rd=(qrand() % 10)-5; //随机数,-5~+5
        y1=qSin(t)+rd/50;
        *series0<<QPointF(t,y1);  //序列添加数据点
//        series0->append(t,y1);  //序列添加数据点

        rd=(qrand() % 10)-5; //随机数,-5~+5
        y2=qCos(t)+rd/50;
//        series1->append(t,y2); //序列添加数据点
        *series1<<QPointF(t,y2); //序列添加数据点

        t+=intv;
    }

}

void MainWindow::updateFromChart()
{
    // 从图表上获取数据更新界面显示
    QChart * aChart = ui->chartView->chart();	// 获取chart
    ui->editTitle->setText(aChart->title());
    QMargins mg = aChart->margins();	// 边距
    ui->spinMarginLeft->setValue(mg.left());
    ui->spinMarginRight->setValue(mg.right());
    ui->spinMarginTop->setValue(mg.top());
    ui->spinMarginBottom->setValue(mg.bottom());
}

void MainWindow::on_btnLegendFont_clicked()
{
    // 图例的字体设置
    QFont font = ui->chartView->chart()->legend()->font();
    bool ok = false;
    font = QFontDialog::getFont(&ok, font);
    if(ok)
        ui->chartView->chart()->legend()->setFont(font);
}

void MainWindow::on_radioSeries0_clicked()
{
    // 获取当前序列数据
    if(ui->radioSeries0->isChecked())
        curSeries = (QLineSeries *)ui->chartView->chart()->series().at(0);
    else
        curSeries = (QLineSeries *)ui->chartView->chart()->series().at(1);

    // 获取序列当前的属性值，并显示到界面上
    ui->editSeriesName->setText(curSeries->name());
    ui->chkSeriesVisible->setChecked(curSeries->isVisible());
    ui->chkPointVisible->setChecked(curSeries->pointsVisible());
    ui->sliderSeriesOpacity->setValue(curSeries->opacity()*10);
    ui->chkPointVisible->setChecked(curSeries->pointLabelsVisible());
}

void MainWindow::on_radioSeries1_clicked()
{
    // 获取当前序列数据
    if(ui->radioSeries0->isChecked())
        curSeries = (QLineSeries *)ui->chartView->chart()->series().at(0);
    else
        curSeries = (QLineSeries *)ui->chartView->chart()->series().at(1);

    // 获取序列当前的属性值，并显示到界面上
    ui->editSeriesName->setText(curSeries->name());
    ui->chkSeriesVisible->setChecked(curSeries->isVisible());
    ui->chkPointVisible->setChecked(curSeries->pointsVisible());
    ui->sliderSeriesOpacity->setValue(curSeries->opacity()*10);
    ui->chkPointVisible->setChecked(curSeries->pointLabelsVisible());
}
