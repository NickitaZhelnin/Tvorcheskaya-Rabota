#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<QPushButton>
#include <QMessageBox>
#include<QPixmap>
#include <QVector>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


QVector<QString> vec;
double sum = 0;


void MainWindow::on_In_system_clicked()
{
   QString Name,Sum;
   Name=ui->Name->text();
   Sum=ui->Sum->text();
   vec.push_back(Name);
   vec.push_back(Sum);
   double tmp = Sum.toDouble();
   sum+=tmp;
}


void MainWindow::on_Delete_all_clicked()
{
    ui->Sum->clear();
    ui->Name->clear();
    ui->Summa_smena->clear();
    ui->Name_2->clear();
    ui->Sum_person->clear();
    sum = 0;
    vec.clear();
}


void MainWindow::on_find_sum_clicked()
{
    QString tmp;
    tmp.setNum(sum);
    ui->Summa_smena->setText(tmp);
}


void MainWindow::on_find_clicked()
{
    QString tmp = ui->Name_2->text();
    QString tmp2;
    for(int i = 0; i < vec.size(); i++)
        if(vec.at(i) == tmp)
            tmp2 = vec.at(i+1);

    ui->Sum_person->setText(tmp2);
}



