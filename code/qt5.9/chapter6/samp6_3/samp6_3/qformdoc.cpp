#include "qformdoc.h"
#include "ui_qformdoc.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFileInfo>

QFormDoc::QFormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFormDoc)
{
    ui->setupUi(this);

    QToolBar *toolBar = new QToolBar(this);
    toolBar->addAction(ui->actOpen);
    toolBar->addAction(ui->actFont);
    toolBar->addSeparator();
    toolBar->addAction(ui->actCut);
    toolBar->addAction(ui->actCopy);
    toolBar->addAction(ui->actPaste);
    toolBar->addAction(ui->actUndo);
    toolBar->addAction(ui->actRedo);
    toolBar->addSeparator();
    toolBar->addAction(ui->actClose);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(toolBar);
    mainLayout->addWidget(ui->plainTextEdit);

    this->setLayout(mainLayout);
}

QFormDoc::~QFormDoc()
{
    delete ui;
}

void QFormDoc::loadFile(QString filename)
{
    QFile aFile(filename);
    if(aFile.open(QIODevice::ReadOnly)){
        QTextStream aStream(&aFile);
        ui->plainTextEdit->clear();
        while(!aStream.atEnd()){
            ui->plainTextEdit->appendPlainText(aStream.readLine());
        }
        aFile.close();

        QFileInfo info(filename);
        QString shortName = info.fileName();
        this->setWindowTitle(shortName);

    }else{
        QMessageBox::warning(this, "错误", "打开文件失败", QMessageBox::Ok, QMessageBox::NoButton);

    }

}

// 打开文件
void QFormDoc::on_actOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "打开文件", "", "选择文件(*.*)");
    if(filename.isEmpty())
        return;
    loadFile(filename);
}
