#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include    <QtCharts>  //必须这么设置
#include    <QStandardItemModel>

QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define fixedColumnCount 5	//数据模型的列数
#define iniDataRowCount 40	//学生个数
#define colNoName	0	//姓名的列编号
#define colNoMath	1	//数学的列编号
#define colNoChinese	2	//语文的列编号
#define colNoEnglish	3	//英语的列编号
#define colNoAverage	4	//平均分的列编号


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QStandardItemModel *theModel;	//数据模型
    void iniData();	//初始化数据
    void surveyData();	//统计数据

    void initBarChart();	//柱状图初始化
    void buildBarChart();	//构建柱状图

private slots:
    void on_itemChanged(QStandardItem *item);


    void on_pushButton_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
