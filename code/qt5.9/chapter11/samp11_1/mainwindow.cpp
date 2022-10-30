#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// 打开数据库
void MainWindow::on_actOpenDB_triggered()
{
    QString aFile = QFileDialog::getOpenFileName(this, "打开数据库", "",
                                                 "数据库文件(*.db *.db3)");
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(aFile);
    if(!DB.open()){
        QMessageBox::warning(this, "错误", "打开数据库失败",
                             QMessageBox::Ok, QMessageBox::NoButton);
    }

    // 打开数据库
    openTable();
}

// 打开数据表
void MainWindow::openTable()
{
    // 设置数据模型
    tabModel = new QSqlTableModel(this, DB);
    tabModel->setTable("employee");
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tabModel->setSort(tabModel->fieldIndex("empNo"), Qt::AscendingOrder);
    if(!tabModel->select()){
        QMessageBox::critical(this, "错误信息",
                              "打开数据库表错误，错误信息\n" + tabModel->lastError().text(),
                              QMessageBox::Ok, QMessageBox::NoButton);
    }

    //model表头字段显示名
    tabModel->setHeaderData(tabModel->fieldIndex("empNo"), Qt::Horizontal, "工号");
    tabModel->setHeaderData(tabModel->fieldIndex("Name"), Qt::Horizontal, "姓名");
    tabModel->setHeaderData(tabModel->fieldIndex("Gender"), Qt::Horizontal, "性别");
    tabModel->setHeaderData(tabModel->fieldIndex("Height"), Qt::Horizontal, "身高");
    tabModel->setHeaderData(tabModel->fieldIndex("Birthday"), Qt::Horizontal, "出生年月");
    tabModel->setHeaderData(tabModel->fieldIndex("Mobile"), Qt::Horizontal, "手机");
    tabModel->setHeaderData(tabModel->fieldIndex("Province"), Qt::Horizontal, "省份");
    tabModel->setHeaderData(tabModel->fieldIndex("City"), Qt::Horizontal, "城市");
    tabModel->setHeaderData(tabModel->fieldIndex("Department"), Qt::Horizontal, "部门");
    tabModel->setHeaderData(tabModel->fieldIndex("Education"), Qt::Horizontal, "学历");
    tabModel->setHeaderData(tabModel->fieldIndex("Salary"), Qt::Horizontal, "工资");

    tabModel->setHeaderData(tabModel->fieldIndex("Memo"), Qt::Horizontal, "备注");
    tabModel->setHeaderData(tabModel->fieldIndex("Photo"), Qt::Horizontal, "照片");

    theSelection=new QItemSelectionModel(tabModel);//关联选择模型
//theSelection当前项变化时触发currentChanged信号
    connect(theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
//选择行变化时
    connect(theSelection,SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this,SLOT(on_currentRowChanged(QModelIndex,QModelIndex)));

    ui->tableView->setModel(tabModel);//设置数据模型
    ui->tableView->setSelectionModel(theSelection); //设置选择模型
    ui->tableView->setColumnHidden(tabModel->fieldIndex("Memo"),true);//隐藏列
    ui->tableView->setColumnHidden(tabModel->fieldIndex("Photo"),true);//隐藏列

//tableView上为“性别”和“部门”两个字段设置自定义代理组件
    QStringList strList;
    strList<<"男"<<"女";
    bool isEditable=false;
    delegateSex.setItems(strList,isEditable);
    ui->tableView->setItemDelegateForColumn(
       tabModel->fieldIndex("Gender"),&delegateSex); //Combbox选择型

    strList.clear();
    strList<<"销售部"<<"技术部"<<"生产部"<<"行政部";
    isEditable=true;
    delegateDepart.setItems(strList,isEditable);
    ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("Department"),&delegateDepart); //Combbox选择型

    // 创建界面组件与数据模型之间的映射关系
    dataMapper = new QDataWidgetMapper();
    dataMapper->setModel(tabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbSpinEmNo, tabModel->fieldIndex("empNo"));
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("Name"));
    dataMapper->addMapping(ui->dbComboSex,tabModel->fieldIndex("Gender"));

    dataMapper->addMapping(ui->dbSpinHeight,tabModel->fieldIndex("Height"));
    dataMapper->addMapping(ui->dbEditBirth,tabModel->fieldIndex("Birthday"));
    dataMapper->addMapping(ui->dbEditMobile,tabModel->fieldIndex("Mobile"));

    dataMapper->addMapping(ui->dbComboProvince,tabModel->fieldIndex("Province"));
    dataMapper->addMapping(ui->dbEditCity,tabModel->fieldIndex("City"));
    dataMapper->addMapping(ui->dbComboDep,tabModel->fieldIndex("Department"));

    dataMapper->addMapping(ui->dbComboEdu,tabModel->fieldIndex("Education"));
    dataMapper->addMapping(ui->dbSpinSalary,tabModel->fieldIndex("Salary"));

    dataMapper->addMapping(ui->dbEditMemo,tabModel->fieldIndex("Memo"));

//    dataMapper->addMapping(ui->dbPhoto,tabModel->fieldIndex("Photo")); //图片无法直接映射
    dataMapper->toFirst();	//移动到首记录(默认显示第一条数据)

    getFieldNames();	//获取字段名称列表,填充ui->groupBoxSort组件

    // 更新action和界面组件的使能状态
    ui->actOpenDB->setEnabled(false);

    ui->actRecAppend->setEnabled(true);
    ui->actRecInsert->setEnabled(true);
    ui->actRecDelete->setEnabled(true);
    ui->actScan->setEnabled(true);

    ui->groupBoxSort->setEnabled(true);
    ui->groupBoxFilter->setEnabled(true);
}

void MainWindow::getFieldNames()
{
    QSqlRecord emptyRec = tabModel->record();	//获取空记录，只有字段明
    for(int i=0; i < emptyRec.count(); ++i)
        ui->comboFields->addItem(emptyRec.fieldName(i));
}


void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    // 更新action状态
    ui->actSubmit->setEnabled(tabModel->isDirty());
    ui->actRevert->setEnabled(tabModel->isDirty());
}

void MainWindow::on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    // 行切换时状态控制
    ui->actRecAppend->setEnabled(current.isValid());
    ui->actPhoto->setEnabled(current.isValid());
    ui->actPhotoClear->setEnabled(current.isValid());

    if(!current.isValid()){
        return;
    }

    dataMapper->setCurrentIndex(current.row());	// 设置dataMapper对应的行数据

    // 设置dataMapper上的图片
    int curRow = current.row();
    QSqlRecord record = tabModel->record(curRow);
    if(record.value("photo").isNull()){
        ui->dbLabPhoto->clear();
    }
    else{
        QByteArray phData= record.value("photo").toByteArray();
        QPixmap pix;
        pix.loadFromData(phData);

        ui->dbLabPhoto->setPixmap(pix.scaled(ui->dbLabPhoto->sizeHint()));
    }

}

// 保存修改
void MainWindow::on_actSubmit_triggered()
{
    bool rec = tabModel->submitAll();
    if(!rec)
        QMessageBox::information(this, "消息",
                                 "数据保存错误，错误信息\n" + tabModel->lastError().text(),
                                 QMessageBox::Ok, QMessageBox::No);
    else{
        ui->actSubmit->setEnabled(false);
        ui->actRevert->setEnabled(false);
    }
}


// 取消修改
void MainWindow::on_actRevert_triggered()
{
    tabModel->revertAll();
    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
}


// 删除当前行
void MainWindow::on_actRecDelete_triggered()
{
    QModelIndex index = theSelection->currentIndex();
    tabModel->removeRow(index.row());
}


// 插入记录
void MainWindow::on_actRecInsert_triggered()
{
    QModelIndex curIndex = theSelection->currentIndex();

    tabModel->insertRow(curIndex.row(), QModelIndex());
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}

// 添加记录
void MainWindow::on_actRecAppend_triggered()
{

    tabModel->insertRow(tabModel->rowCount(), QModelIndex()); // 在末尾添加一个记录

    // 设置选择行
    QModelIndex curIndex = tabModel->index(tabModel->rowCount()-1, 1);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex,  QItemSelectionModel::Select);


    int currRow = curIndex.row();
    tabModel->setData(tabModel->index(currRow, 0), 2000+tabModel->rowCount());	//自动生成编号
    tabModel->setData(tabModel->index(currRow, 2), "男");
}

// 设置照片
void MainWindow::on_actPhoto_triggered()
{
    QString aFile = QFileDialog::getOpenFileName(
                    this, "打开照片", "", "照片(*.jpg)");

    if(aFile.isEmpty())
        return;

    QByteArray data;
    QFile *file = new QFile(aFile);
    file->open(QIODevice::ReadOnly);
    data = file->readAll();
    file->close();

    // 设置模型里面的photo数据
    int curRow = theSelection->currentIndex().row();
    QSqlRecord curRecord = tabModel->record(curRow);
    curRecord.setValue("photo", data);
    tabModel->setRecord(curRow, curRecord);

    // 设置lab的数据
    QPixmap pix = QPixmap();
    pix.loadFromData(data);
    ui->dbLabPhoto->setPixmap(pix.scaled(ui->dbLabPhoto->sizeHint()));
}

// 清除照片
void MainWindow::on_actPhotoClear_triggered()
{
    int curRow = theSelection->currentIndex().row();
    QSqlRecord record = tabModel->record(curRow);

    record.setNull("photo");
    tabModel->setRecord(curRow, record);

    ui->dbLabPhoto->clear();
}

// 升序
void MainWindow::on_radioBtnAscend_clicked()
{
    tabModel->setSort(ui->comboFields->currentIndex(), Qt::AscendingOrder);
    tabModel->select();
}

// 降序
void MainWindow::on_radioButtonDescend_clicked()
{
    tabModel->setSort(ui->comboFields->currentIndex(), Qt::DescendingOrder);
    tabModel->select();
}


void MainWindow::on_radioBtnMan_clicked()
{
    tabModel->setFilter("Gender = '男' ");
}

void MainWindow::on_radioBtnWoman_clicked()
{
    tabModel->setFilter("Gender = '女' ");
}

void MainWindow::on_radioButton_3_clicked()
{

    tabModel->setFilter("");
}


// 选择字段进行排序
void MainWindow::on_comboFields_currentIndexChanged(int index)
{
    if(ui->radioBtnAscend->isChecked())
        tabModel->setSort(index, Qt::AscendingOrder);
    else
        tabModel->setSort(index, Qt::DescendingOrder);

    tabModel->select();
}

// 涨工资
void MainWindow::on_actScan_triggered()
{
    if(tabModel->rowCount() == 0)
        return;

    for(int i=0; i < tabModel->rowCount(); ++i){
        QSqlRecord record = tabModel->record(i);
        float salary = record.value("Salary").toFloat();
        salary = salary * 1.1;
        record.setValue("Salary", salary);
        tabModel->setRecord(i, record);
    }

    if(tabModel->submitAll())
        QMessageBox::information(this, "消息", "涨工资计算完毕",
                                 QMessageBox::Ok, QMessageBox::No);

}
















