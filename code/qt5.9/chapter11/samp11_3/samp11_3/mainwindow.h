#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QItemSelectionModel>

#include "wdialogdata.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSqlDatabase DB;	//数据库
    QSqlQueryModel *qryModel;	//数据库模型
    QItemSelectionModel *theSelection;	//选择模型
    void openTable();	// 打开数据表
    void updateRecord(int recNo);	//更新记录

private slots:
    void on_actOpenDB_triggered();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
