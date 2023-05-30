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

/*
void MainWindow::on_Summa_clicked()
{
    ui->label_SUM->setText("Ежемесячный платеж:");
    ui->label_ST->setText("Годовая ставка(%)");
    ui->label_SROK->setText("На какой срок(мес): ");
    ui->label_ITOG->setText("Сумма кредита(руб):");
}


void MainWindow::on_Srok_clicked()
{
    ui->label_SUM->setText("Сумма кредита(руб): ");
    ui->label_ST->setText("Годовая ставка(%)");
    ui->label_SROK->setText("Ежемесячный платеж: ");
    ui->label_ITOG->setText("На какой срок(мес): ");
}


void MainWindow::on_Calculate_ST_clicked()
{
    QString tmp;
    double Stavka,Sum,Months, Pay_Months;
    tmp=ui->Stavka->text(); Stavka=tmp.toDouble();
    tmp=ui->Sum->text();Sum=tmp.toDouble();
    tmp=ui->Months->text();Months=tmp.toDouble();

    Pay_Months=(((Stavka*Months)/Sum)-1)*100;
    QString new_Pay;
    new_Pay.setNum(Pay_Months);

    ui->Pay->setText(new_Pay);
}


void MainWindow::on_Calculate_SUM_2_clicked()
{
    QString tmp;
    double Sum,Months, Pay_Months;
    tmp=ui->Sum->text();Sum=tmp.toDouble();
    tmp=ui->Months->text();Months=tmp.toDouble();
    Pay_Months=Sum*Months;
    QString new_Pay;
    new_Pay.setNum(Pay_Months);

    ui->Pay->setText(new_Pay);
}


void MainWindow::on_Calculate_srok_clicked()
{
    QString tmp;
    double Stavka,Sum,Months, Pay_Months;
    tmp=ui->Stavka->text(); Stavka=tmp.toDouble();
    tmp=ui->Sum->text();Sum=tmp.toDouble();
    tmp=ui->Months->text();Months=tmp.toDouble();

    Stavka=(Stavka)/100;
    Pay_Months=((Stavka*Sum)+Sum)/Months;

    QString new_Pay;
    new_Pay.setNum(Pay_Months);

    ui->Pay->setText(new_Pay);
}

*/

