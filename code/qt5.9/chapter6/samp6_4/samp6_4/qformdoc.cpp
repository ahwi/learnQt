#include "qformdoc.h"
#include "ui_qformdoc.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QFontDialog>

QFormDoc::QFormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFormDoc)
{
    ui->setupUi(this);
}

QFormDoc::~QFormDoc()
{
    delete ui;
}

void QFormDoc::loadFromFile(QString &filename)
{
    QFile aFile(filename);
    if(aFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&aFile);
        while(!stream.atEnd()){
            ui->plainTextEdit->appendPlainText(stream.readLine());
        }
        aFile.close();

        mCurrentFile = filename;
        QFileInfo info(filename);
        QString shortName = info.fileName();
        this->setWindowTitle(shortName);
        mFileOpened=true;
    }
}

QString QFormDoc::currentFileName()
{
    return mCurrentFile;
}

bool QFormDoc::isFileOpened()
{
    return mFileOpened;
}

void QFormDoc::setEditFont()
{
    QFont font = ui->plainTextEdit->font();

    bool ok = false;
    font = QFontDialog::getFont(&ok, font);
    ui->plainTextEdit->setFont(font);
}

void QFormDoc::textCut()
{
    ui->plainTextEdit->cut();
}

void QFormDoc::textCopy()
{
    ui->plainTextEdit->copy();
}

void QFormDoc::textPaste()
{
    ui->plainTextEdit->paste();
}
