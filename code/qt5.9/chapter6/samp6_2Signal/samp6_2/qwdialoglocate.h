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

signals:
    void changeActionEnable(bool enable);


private:
    Ui::QWDialogLocate *ui;
};

#endif // QWDIALOGLOCATE_H
