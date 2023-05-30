#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_In_system_clicked();
    void on_Delete_all_clicked();
    void on_find_sum_clicked();
    void on_find_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
