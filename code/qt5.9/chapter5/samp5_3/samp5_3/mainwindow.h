#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#define FixedColumnCount 6	// 文本固定6列

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
    QLabel *LabCurFile;	//当前文件
    QLabel *LabCellPos;	// 当前单元格行列号
    QLabel *LabCellText;	// 当前单元格内容

    QStandardItemModel *theModel;	// 数据模型
    QItemSelectionModel *theSelection;	//Item选择模型

    void iniModelFromStringList(QStringList &);	// 从StringList初始化数据模型

private slots:
    // 当前选择单元格发生变化
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actOpen_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
