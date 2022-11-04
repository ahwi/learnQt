#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    // 新建文件
    void on_actDoc_New_triggered();

    // 打开文件
    void on_actDoc_Open_triggered();

    // MDI显示模式切换
    void on_actViewMode_triggered(bool checked);

    // 窗口级联展开
    void on_actCascade_triggered();

    // 平铺展开
    void on_actTile_triggered();

    // 关闭全部子窗口
    void on_actCloseALL_triggered();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
