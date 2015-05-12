#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    numberOfData = 0;
//    dataC.insert(0,10);
//    dataC.insert(1,15);
//    dataC.insert(2,5);
//    dataT.insert(0,30);
//    dataT.insert(1,40);
//    dataT.insert(2,50);

    //dataC = new QVector<int>();
   // dataT = new QVector<int>();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()//Добавить (забыл перейменовать)
{
    if((ui->CEdit->text().isEmpty()) || (ui->TEdit->text().isEmpty()))
    {
        ui->errorLabel->setText("Заполните все поля!");
        return;
    }
    if((ui->CEdit->text().toInt() == 0) || (ui->TEdit->text().toInt() == 0))
    {
        ui->errorLabel->setText("Введите число отличное от 0!");
        return;
    }
    dataC.insert(numberOfData,ui->CEdit->text().toInt());
    dataT.insert(numberOfData,ui->TEdit->text().toInt());
    numberOfData++;
    ui->CEdit->setText("");
    ui->TEdit->setText("");
    ui->labelC->setText("C"+QString::number(numberOfData));
    ui->labelT->setText("T"+QString::number(numberOfData));
    ui->errorLabel->setText("");


}

void MainWindow::on_pushButton_2_clicked()//Очистка (забыл перейменовать)
{
    ui->checkRT->setText(" ");
    dataC.remove(0,dataC.size());
    dataT.remove(0,dataT.size());
    numberOfData = 0;
    ui->CEdit->setText("");
    ui->TEdit->setText("");
    ui->labelC->setText("C"+QString::number(numberOfData));
    ui->labelT->setText("T"+QString::number(numberOfData));
    ui->textBrowser->clear();
    ui->checkUB->setText("");
    ui->checkEDF->setText("");
    ui->EDFRez->setText("");
    ui->UBRez->setText("");

}

void MainWindow::on_pushButton_3_clicked()//Начать тесты (забыл перейменовать)
{
    ui->textBrowser->clear();
    if(numberOfData!=0)
    {
        double EDFandUB = 0;
        for(int i = 0;i<numberOfData;i++)
        {
            EDFandUB += (double)dataC[i] / (double)dataT[i];
        }
        //EDF test
        ui->EDFRez->setText(QString::number(EDFandUB)+"<= 1?");
        if (EDFandUB<=1)
            ui->checkEDF->setText("passed");
        else
            ui->checkEDF->setText("failed");
        //UB test
        ui->UBRez->setText(QString::number(EDFandUB)+"<="+QString::number(numberOfData*(pow(2.0,1.0/(double)numberOfData)-1.0))+"?");
        if (EDFandUB <= (double)numberOfData*(pow(2,1.0/(double)numberOfData)-1))
            ui->checkUB->setText("passed");
        else
            ui->checkUB->setText("failed");
        //RT test
        double R0 = 0;
        double R1 = 0;
        for(int j = 0; j<numberOfData;j++)
        {
            for(int i = 0;i<=j;i++)
            {
                R0 +=dataC[i];
            }
            if(j==0)
                R1 = R0;
            else
            {
                R1 = dataC[j];
                for(int i=j;i>0;i--)
                {
                    R1 +=(int)(R0/dataT[j-i]+0.5)*dataC[j-i];
                    qDebug()<<"j="<<j<<"i="<<i;
                    qDebug()<<R0<<dataT[j-i]<<dataC[j-i];
                }
            }

            ui->textBrowser->append("R0["+QString::number(j)+"]: "
                                    +QString::number(R0));
            if(R1<=dataT[j])
            {
                ui->textBrowser->append("R1["+QString::number(j)+"]: "
                                        +QString::number(R1)+"<="+QString::number(dataT[j])+" passed");
                ui->checkRT->setText("passed");
            }
            else
            {
                ui->textBrowser->append("R1["+QString::number(j)+"]: "
                                        +QString::number(R1)+"<="+QString::number(dataT[j])+" failed");
                ui->checkRT->setText("failed");
                return;
            }
        R0 = 0;
        }
    }
}

