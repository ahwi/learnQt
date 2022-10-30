#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    theModel = new QStandardItemModel(iniDataRowCount, fixedColumnCount, this);
    iniData();	//初始化数据
    surveyData();	//数据统计
    connect(theModel, SIGNAL(itemChanged(QStandardItem *)),
            this, SLOT(on_itemChanged(QStandardItem *)));

    ui->tableView->setModel(theModel);

    initBarChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::iniData()
{
    // 数据初始化
    QStringList headerList;
    headerList<<"姓名"<<"数学"<<"语文"<<"英语"<<"平均分";
    theModel->setHorizontalHeaderLabels(headerList);	//设置表头文字
    qsrand(QTime::currentTime().second()); //随机种子
    for(int i=0; i<theModel->rowCount(); i++)
    {
        QString stuName = QString::asprintf("学生%2d", i+1);
        QStandardItem *aItem = new QStandardItem(stuName); //创建item
        aItem->setTextAlignment(Qt::AlignHCenter);
        theModel->setItem(i, colNoName, aItem);	//学生列，设置item
        qreal avgScore = 0;
        for(int j=colNoMath; j<=colNoEnglish; j++) //数学,语文,英语
        {
            //不包含最后一列
            qreal score = 50.0 + (qrand() % 50);	//随机数
            avgScore += score;
            aItem = new QStandardItem(QString::asprintf("%.0f",score));
            aItem->setTextAlignment(Qt::AlignHCenter);
            theModel->setItem(i, j, aItem);	//设置Item
        }
        aItem = new QStandardItem(QString::asprintf("%.1f", avgScore/3));	//平均分
        aItem->setTextAlignment(Qt::AlignHCenter);
        aItem->setFlags(aItem->flags() & (!Qt::ItemIsEditable));	//设置不能编辑
        theModel->setItem(i, colNoAverage, aItem);
    }
}



void MainWindow::surveyData()
{

}

void MainWindow::on_itemChanged(QStandardItem *item)
{
    //自动计算平均分
    if((item->column()<colNoMath) || (item->column()>colNoEnglish))
        return;	//如果被修改的item不是数学、语文、英语就退出
    int rowNo = item->row();	//获取数据的行编号
    qreal avg=0;
    QStandardItem *aItem;
    for(int i=colNoMath; i<=colNoEnglish; i++)
    {
        //获取三个分数的和
        aItem = theModel->item(rowNo, i);
        avg += aItem->text().toDouble();
    }
    avg = avg/3;	//计算平均分
    aItem = theModel->item(rowNo, colNoAverage);	//获取平均分数据的item
    aItem->setText(QString::asprintf("%.1f", avg));
}



void MainWindow::initBarChart()
{
    // 柱状图初始化
    QChart *chart = new QChart();
    chart->setTitle("Barchart演示");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartViewBar->setChart(chart);
    ui->chartViewBar->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::buildBarChart()
{
    //构造柱状图
    QChart *chart = ui->chartViewBar->chart();	//获取ChartView关联的chart
    chart->removeAllSeries();	//删除所有序列
    chart->removeAxis(chart->axisX());	//删除坐标轴
    chart->removeAxis(chart->axisY());	//删除坐标轴

    // 创建三个QBarSet数据集，从数据模型的表头获取Name
    QBarSet *setMath = new QBarSet(theModel->horizontalHeaderItem(colNoMath)->text());
    QBarSet *setChinese = new QBarSet(theModel->horizontalHeaderItem(colNoChinese)->text());
    QBarSet *setEnglish = new QBarSet(theModel->horizontalHeaderItem(colNoEnglish)->text());
    QLineSeries *Line = new QLineSeries();	//用于显示平均分
    Line->setName(theModel->horizontalHeaderItem(colNoAverage)->text());
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    Line->setPen(pen);

    for(int i=0; i<theModel->rowCount(); i++){
        // 从数据模型获取数据
        setMath->append(theModel->item(i, colNoMath)->text().toInt());
        setChinese->append(theModel->item(i, colNoChinese)->text().toInt());
        setEnglish->append(theModel->item(i, colNoEnglish)->text().toInt());
        Line->append(QPointF(i, theModel->item(i, colNoAverage)->text().toFloat()));
    }

    // 创建一共柱状图序列QBarSeries，并添加三个数据集
    QBarSeries *series = new QBarSeries();
    series->append(setMath);
    series->append(setChinese);
    series->append(setEnglish);
    chart->addSeries(series);	//添加柱状图序列
    chart->addSeries(Line);		//添加折线图序列

    //用于横坐标的字符串列表，即学生姓名
    QStringList categories;
    for(int i=0; i<theModel->rowCount(); i++)
        categories << theModel->item(i, colNoName)->text();
    //用于柱状图的横坐标轴
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);	//添加横坐标文字列表
    chart->setAxisX(axisX, series);	//设置横坐标
    chart->setAxisX(axisX, Line);	//设置横坐标
    axisX->setRange(categories.at(0), categories.at(categories.count() - 1));

    //数值型坐标作为纵坐标轴
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 100);
    axisY->setTitleText("分数");
    axisY->setTickCount(6);
    axisY->setLabelFormat("%.0f");	//标签格式
    chart->setAxisY(axisY, series);
    chart->setAxisY(axisY, Line);
    chart->legend()->setVisible(true);	//显示图例
    chart->legend()->setAlignment(Qt::AlignBottom);	//图例显示在下方
}

void MainWindow::on_pushButton_clicked()
{
    buildBarChart();
}
