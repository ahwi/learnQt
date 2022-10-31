#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "qwdialogsize.h"
#include "qwdialogheaders.h"

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
    QStandardItemModel *theModel;	// 数据模型
    QItemSelectionModel *theSelection;	//item选择模型

    QWDialogHeaders *dlgSetHeaders=NULL;	//设置表格标题对话框

private slots:
    void on_actTab_SetSize_triggered();

    void on_actTab_SetHeader_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
