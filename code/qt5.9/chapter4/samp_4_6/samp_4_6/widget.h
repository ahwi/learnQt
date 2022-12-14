#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnIniItems_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_btnToComboBox_clicked();

    void on_plainTextEdit_customContextMenuRequested(const QPoint &pos);

    void on_btnClearText_clicked();

    void on_chkBoxEditable_clicked(bool checked);

    void on_chkBoxReadonly_clicked(bool checked);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
