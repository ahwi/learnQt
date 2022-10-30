#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;
class QPixmap;
class QTreeWidgetItem;


class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actAddFolder_triggered();

    void on_actAddFiles_triggered();

    void on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actDeleteItem_triggered();

    void on_actScanItems_triggered();

    void on_actZoomFitH_triggered();

    void on_actZoomOut_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomRealSize_triggered();


    void on_actDockVisible_triggered(bool checked);

    void on_actDockFloat_triggered(bool checked);

    void on_dockWidget_visibilityChanged(bool visible);

    void on_dockWidget_topLevelChanged(bool topLevel);

private:
    // 枚举类型treeItemType, 创建节点时用作type参数，自定义类型必须打羽1000
    enum treeItemType{itTopItem=1001, itGroupItem, itImageItem};
    enum treeColNum{colItem=0, colItemType=1};	// 目录树列的编号

    QLabel *LabFileName;	//用于状态栏文件名显示
    QPixmap curPixmap;	//当前的图片
    float pixRatio;	//当前的图片

    //目录树初始化
    void initTree();
    // 添加目录
    void addFolderItem(QTreeWidgetItem *parItem, QString dirName);
    // 提取目录名称
    QString getFinalFolderNmae(const QString &fullPathName);
    // 添加图片
    void addImageItem(QTreeWidgetItem *parItem, QString aFilename);
    // 显示一个图片节点的图片
    void displayImage(QTreeWidgetItem *item);
    // 遍历改变节点标题
    void changeItemCaption(QTreeWidgetItem *item);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
