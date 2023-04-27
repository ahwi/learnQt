#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHostInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

public:
    QString protocolName(QAbstractSocket::NetworkLayerProtocol protocol);

private slots:
    void on_btnGetHostInfo_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
