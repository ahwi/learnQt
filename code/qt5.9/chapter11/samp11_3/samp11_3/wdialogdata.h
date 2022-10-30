#ifndef WDIALOGDATA_H
#define WDIALOGDATA_H

#include <QDialog>
#include <QSqlRecord>


namespace Ui {
class WDialogData;
}

class WDialogData : public QDialog
{
    Q_OBJECT

public:
    explicit WDialogData(QWidget *parent = nullptr);
    ~WDialogData();

private:
    QSqlRecord mRecord;	//保存一条记录的数据

public:

    // 更新记录
    void setUpdateRecord(QSqlRecord &recData);


private:
    Ui::WDialogData *ui;
};

#endif // WDIALOGDATA_H
