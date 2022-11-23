#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initGraphicsSystem();	//创建Graphics View的各项

private:
    QLabel *labViewCord;
    QLabel *labSceneCord;
    QLabel *labItemCord;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
