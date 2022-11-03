#ifndef QWDIALOGLOCATE_H
#define QWDIALOGLOCATE_H

#include <QDialog>

namespace Ui {
class QWDialogLocate;
}

class QWDialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogLocate(QWidget *parent = nullptr);
    ~QWDialogLocate();

protected:
    void closeEvent(QCloseEvent *e);
    void showEvent(QShowEvent *e);


private slots:
    void on_btnClose_clicked();

    void on_btnSetText_clicked();

    void setRowColumn(int row, int column);

signals:
    void changeActionEnable(bool enable);
    void setACellContent(int row, int column, QString text);


private:
    Ui::QWDialogLocate *ui;
};

#endif // QWDIALOGLOCATE_H
