#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDataWidgetMapper>

#include "qwcomboboxdelegate.h"


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

    QSqlDatabase DB; //数据库连接
    QSqlTableModel *tabModel;	//数据模型
    QItemSelectionModel *theSelection;	//选择模型
    QDataWidgetMapper *dataMapper;	//数据映射

    QWComboBoxDelegate delegateSex;	//自定义数据代理，性别
    QWComboBoxDelegate delegateDepart;	//自定义数据代理，部门

    void openTable();	//打开数据表
    void getFieldNames();	// 获取字段名称，填充"排序字段"的comboBox
private slots:
    void on_actOpenDB_triggered();

    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actSubmit_triggered();

    void on_actRevert_triggered();

    void on_actRecDelete_triggered();

    void on_actRecInsert_triggered();

    void on_actRecAppend_triggered();

    void on_actPhoto_triggered();

    void on_actPhotoClear_triggered();

    void on_radioBtnAscend_clicked();

    void on_radioButtonDescend_clicked();

    void on_radioBtnMan_clicked();

    void on_radioBtnWoman_clicked();

    void on_radioButton_3_clicked();

    void on_comboFields_currentIndexChanged(int index);

    void on_actScan_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
