#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidgetItem>
#include <QFileDialog>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LabFileName = new QLabel("");
    ui->statusbar->addWidget(LabFileName);
    this->setCentralWidget(ui->scrollArea);
    initTree();	//初始化目录树

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTree()
{
    // 初始化目录树
    QString dataStr = "";	// item的data存储的string
    ui->treeFiles->clear();

    QIcon icon;
    icon.addFile(":images/icons/15.ico");

    QTreeWidgetItem* item = new QTreeWidgetItem(MainWindow::itTopItem);
    item->setIcon(MainWindow::colItem, icon);
    item->setText(MainWindow::colItem, "图片文件");
    item->setText(MainWindow::colItemType, "type=itTopItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |
                   Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);

    item->setData(MainWindow::colItem, Qt::UserRole, QVariant(dataStr));
    ui->treeFiles->addTopLevelItem(item);	//添加顶层节点
}

// 添加一个组节点
void MainWindow::addFolderItem(QTreeWidgetItem *parItem, QString dirName)
{
    QIcon icon(":/images/icons/open3.bmp");
    QString NodeText = getFinalFolderNmae(dirName);	//获取最后的文件夹名称

    QTreeWidgetItem *item;
    item = new QTreeWidgetItem(MainWindow::itGroupItem);
    item->setIcon(MainWindow::colItem, icon);
    item->setText(MainWindow::colItem, NodeText);
    item->setText(MainWindow::colItemType, "type=itGroupItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled |
                   Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);
    item->setData(colItem, Qt::UserRole, QVariant(dirName));
    parItem->addChild(item);	//在父节点下面添加子节点
}

// 从一个完整目录名称里，获得最后的文件夹名称
QString MainWindow::getFinalFolderNmae(const QString &fullPathName)
{
    int cnt = fullPathName.length();
    int i = fullPathName.lastIndexOf("/");
    QString str = fullPathName.right(cnt-i-1);
    return str;
}

// 添加一个图片节点
void MainWindow::addImageItem(QTreeWidgetItem *parItem, QString aFilename)
{
    QIcon icon(":/images/icons/31.bmp");
    QString NodeText = getFinalFolderNmae(aFilename);	//获取最后的文件名称

    QTreeWidgetItem *item;
    item = new QTreeWidgetItem(MainWindow::itImageItem);
    item->setIcon(MainWindow::colItem, icon);
    item->setText(MainWindow::colItem, NodeText);
    item->setText(MainWindow::colItemType, "type=itImageItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled |
                   Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);
    item->setData(colItem, Qt::UserRole, QVariant(aFilename));
    parItem->addChild(item);	//在父节点下面添加子节点

}

// 显示图片，节点item存储了图片文件名
void MainWindow::displayImage(QTreeWidgetItem *item)
{

    QString filename = item->data(MainWindow::colItem, Qt::UserRole).toString();	//文件名
    LabFileName->setText(filename);
    curPixmap.load(filename);
    on_actZoomFitH_triggered();	// 自动适应图片高度

    ui->actZoomFitH->setEnabled(true);
    ui->actZoomFitW->setEnabled(true);
    ui->actZoomIn->setEnabled(true);
    ui->actZoomOut->setEnabled(true);
    ui->actZoomRealSize->setEnabled(true);
}

// 改变节点的标题文字
void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{
    QString str = "*" + item->text(colItem);	//节点标题前加“*”
    item->setText(colItem, str);
    if(item->childCount() <= 0)
        return;
    for(int i=0; i < item->childCount(); i++)	//遍历子节点
        changeItemCaption(item->child(i));	//调用自己，可重入的函数
}

void MainWindow::on_actAddFolder_triggered()
{
    // 添加组节点
    QString dir = QFileDialog::getExistingDirectory();	//选择目录
    if(!dir.isEmpty())
    {
        QTreeWidgetItem *parItem = ui->treeFiles->currentItem();	//当前节点
        addFolderItem(parItem, dir); // 在父节点下面添加一个组节点
    }
}


// 添加图片文件节点
void MainWindow::on_actAddFiles_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "选择一个或多个文件",  "", "Images(*.jpg)");
    if(files.isEmpty())
        return;

    QTreeWidgetItem *parItem, *item;
    item = ui->treeFiles->currentItem();
    if(item->type() == itImageItem)	// 判断当前节点是否是图片节点
        parItem = item->parent();
    else
        parItem = item;

    for(int i=0; i<files.size(); ++i)
    {
        QString aFilename = files.at(i);	//得到一个文件名
        addImageItem(parItem, aFilename);	//添加一个图片节点
    }
}

void MainWindow::on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);
    if(current==NULL)
        return;
    int var = current->type();	//节点的类型
    switch(var)
    {
        case itTopItem:	//顶层节点
            ui->actAddFolder->setEnabled(true);
            ui->actAddFiles->setEnabled(true);
            ui->actDeleteItem->setEnabled(false);	//顶层节点不能删除
            break;
        case itGroupItem:	//组节点
            ui->actAddFolder->setEnabled(true);
            ui->actAddFiles->setEnabled(true);
            ui->actDeleteItem->setEnabled(true);
            break;
        case itImageItem:	//图片文件节点
            ui->actAddFolder->setEnabled(false);	//图片节点下不能添加目录节点
            ui->actAddFiles->setEnabled(true);
            ui->actDeleteItem->setEnabled(true);
            displayImage(current);	//显示图片
            break;
    }
}

//删除节点
void MainWindow::on_actDeleteItem_triggered()
{
    QTreeWidgetItem *item = ui->treeFiles->currentItem();	//当前节点
    QTreeWidgetItem *parItem =  item->parent();	//父节点
    parItem->removeChild(item);	//移除一个子节点，并不会删除
    delete item;
}

// 遍历节点
void MainWindow::on_actScanItems_triggered()
{
    for(int i=0; i < ui->treeFiles->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->treeFiles->topLevelItem(i);	//顶层节点
        changeItemCaption(item);	//更改节点标题
    }

}

// 适应图片高度显示图片
void MainWindow::on_actZoomFitH_triggered()
{
    // 适应高度显示图片
    int H = ui->scrollArea->height();
    int realH = curPixmap.height();
    pixRatio = float(H) / realH;	//当前显示比例，必须转换为浮点数
    QPixmap pix = curPixmap.scaledToHeight(H-30);	//图片缩放到指定高度
    ui->LabPicture->setPixmap(pix);
}

// 缩小显示
void MainWindow::on_actZoomOut_triggered()
{
    pixRatio = pixRatio * 0.8;
    int w = pixRatio * curPixmap.width();
    int h = pixRatio * curPixmap.height();
    QPixmap pix = curPixmap.scaled(w, h);
    ui->LabPicture->setPixmap(pix);
}

//放大显示
void MainWindow::on_actZoomIn_triggered()
{
    pixRatio = pixRatio * 1.2;
    int w = pixRatio * curPixmap.width();
    int h = pixRatio * curPixmap.height();
    QPixmap pix = curPixmap.scaled(w, h);
    ui->LabPicture->setPixmap(pix);
}

// 实际大小显示
void MainWindow::on_actZoomRealSize_triggered()
{
    pixRatio = 1;
    ui->LabPicture->setPixmap(curPixmap);
}

// 停靠区可见性变化
void MainWindow::on_actDockVisible_triggered(bool checked)
{
    ui->dockWidget->setVisible(checked);
}

void MainWindow::on_actDockFloat_triggered(bool checked)
{
    // 停靠区浮动性
    ui->dockWidget->setFloating(checked);
}


// 停靠区可见性变化
void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    ui->actDockVisible->setChecked(visible);
}

// 停靠区浮动性变化
void MainWindow::on_dockWidget_topLevelChanged(bool topLevel)
{
    ui->actDockFloat->setChecked(topLevel);
}
