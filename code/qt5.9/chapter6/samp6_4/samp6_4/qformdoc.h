#ifndef QFORMDOC_H
#define QFORMDOC_H

#include <QWidget>

namespace Ui {
class QFormDoc;
}

class QFormDoc : public QWidget
{
    Q_OBJECT

public:
    explicit QFormDoc(QWidget *parent = nullptr);
    ~QFormDoc();

public:
    // 打开文件
    void loadFromFile(QString &filename);

    QString currentFileName();

    // 文件是否打开
    bool isFileOpened();

    // 设置字体
    void setEditFont();

    void textCut();

    void textCopy();

    void textPaste();

private:
    QString mCurrentFile; 	//当前文件
    bool mFileOpened=false;	//文件已打开
private:
    Ui::QFormDoc *ui;
};

#endif // QFORMDOC_H
