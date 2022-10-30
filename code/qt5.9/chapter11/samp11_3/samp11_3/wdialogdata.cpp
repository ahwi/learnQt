#include "wdialogdata.h"
#include "ui_wdialogdata.h"

WDialogData::WDialogData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WDialogData)
{
    ui->setupUi(this);
}

WDialogData::~WDialogData()
{
    delete ui;
}


// 编辑记录，更新记录到界面
void WDialogData::setUpdateRecord(QSqlRecord &recData)
{
    mRecord = recData;
    ui->spinEmpNo->setEnabled(false);	//员工编号不允许编辑
    setWindowTitle("更新记录");
    ui->spinEmpNo->setValue(recData.value("EmpNo").toInt());
    ui->editName->setText(recData.value("Name").toString());
    ui->comboSex->setCurrentText(recData.value("Gender").toString());
    ui->spinHeight->setValue(recData.value("Height").toFloat());
    ui->editBirth->setDate(recData.value("Birthday").toDate());
    ui->editMobile->setText(recData.value("Mobile").toString());
    ui->comboProvince->setCurrentText(recData.value("Province").toString());
    ui->editCity->setText(recData.value("City").toString());
    ui->comboDep->setCurrentText(recData.value("Department").toString());
    ui->comboEdu->setCurrentText(recData.value("Education").toString());
    ui->spinSalary->setValue(recData.value("Salary").toInt());
    ui->editMemo->setPlainText(recData.value("Memo").toString());

    QVariant vaPic = recData.value("Photo");
    if(vaPic.isNull())
        ui->LabPhoto->clear();
    else{
        QByteArray picData = vaPic.toByteArray();
        QPixmap pic = QPixmap();
        pic.loadFromData(picData);
        ui->LabPhoto->setPixmap(pic.scaledToWidth(ui->LabPhoto->sizeHint().width()));
    }



}
