#include "balancewindow.h"
#include "ui_balancewindow.h"
#include "panelwindow.h"
#include "ui_panelwindow.h"
#include "common.h"
balanceWindow::balanceWindow(panelWindow* panelPage,vector<transactions>&translist,vector<cards>& bank,vector<users>&account ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::balanceWindow)
{
    ui->setupUi(this);
    QWidget::setWindowIcon(QIcon(":/new/prefix1/elite - Copy.png"));
    QWidget::setWindowTitle("Elite Bank - Check Balance");
    extern int userind;
    this->bank=bank;
    this->panelPage=panelPage;
    ui->Bverify->setIcon(QIcon(":/new/prefix1/check.png"));
    ui->Bverify->setIconSize(QSize(33,33));
    ui->Bverify->setStyleSheet("QPushButton {border-radius:30px;margin: 0;background-color:white;}""QPushButton:hover{background-color:rgb(0,255,0);border-radius:30px;margin: 0;}");
    ui->CBgetCard->setStyleSheet("QComboBox {color:black;background-color:transparent;}""QComboBox:hover{border-radius:10px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));}");
    node<cards>*tmp=account[userind].getLl().get_head();
    ui->CBgetCard->clear();
    ui->CBgetCard->addItem("Choose Card");
    while(tmp!=nullptr)
    {
      ui->CBgetCard->addItem(QString::fromStdString(tmp->get_data().getAcc_number()));
      tmp=tmp->get_next();
    }
    this->account=account;
    this->translist=translist;
    ui->GNumber->setPlaceholderText("Account Number");
    ui->Bbalance->setStyleSheet("QPushButton {color:black;background-color:transparent;}""QPushButton:hover{border-radius:15px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));}");
    ui->Bbalance->setIcon(QIcon(":/new/prefix1/wallet (1).png"));
    ui->Bbalance->setIconSize(QSize(40,40));
    ui->Bback->setStyleSheet("QPushButton {color:black;background-color:transparent;}""QPushButton:hover{border-radius:15px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 11, 11, 255), stop:1 rgba(255, 81, 154, 255));}");
    ui->Bback->setIcon(QIcon(":/new/prefix1/return.png"));
    ui->Bback->setIconSize(QSize(40,50));
    setStyleSheet("balanceWindow {background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:1, stop:0.284974 rgba(255, 37, 179, 255), stop:1 rgba(37, 243, 255, 255));};");
}

balanceWindow::~balanceWindow()
{
    delete ui;
}

void balanceWindow::on_Bback_clicked()
{
    panelPage->show();
       this->hide();
}
void balanceWindow::update_info(vector<cards>&bank,vector<users>&account)
{
    this->bank=bank;
    this->account=account;
    node<cards>*tmp=account[userind].getLl().get_head();
    ui->CBgetCard->clear();
    ui->CBgetCard->addItem("Choose Card");
    while(tmp!=nullptr)
    {
      ui->CBgetCard->addItem(QString::fromStdString(tmp->get_data().getAcc_number()));
      tmp=tmp->get_next();
    }
}
void balanceWindow::on_Bbalance_clicked()
{
    QString number=ui->GNumber->text();
    if(ui->GNumber->text()=="")
    {
        ui->error->setText("Account Number Field Cannot be Empty");
        return;
    }
    node<cards>* tmp=account[userind].getLl().get_head();
    while(tmp!=nullptr)
    {
        if(number.toStdString()==tmp->get_data().getAcc_number())
        {
            for (int i=0;i<account.size();i++)
            {
                if(account[i].getUsername()==tmp->get_data().getUsername())
                    for (int j=0;j<bank.size();j++)
                    {
                        if((bank[j].getUsername()==tmp->get_data().getUsername())&&(bank[j].getCard_number()==tmp->get_data().getCard_number()))
                        {
                            ui->Name->setText("Account Holder : "+QString::fromStdString(account[i].getName())+" "+QString::fromStdString(account[i].getFamily()));
                            ui->Balance->setText("Current Balance : "+QString::fromStdString( to_string(bank[j].getBalance()))+" Rials");
                            ui->error->setText("");
                            return;
                        }
                    }

            }
        }
        else tmp=tmp->get_next();
    }
    if(tmp==nullptr)
    {
        ui->error->setText("Invalid Account Number");
        ui->Name->setText("Account Holder : ");
        ui->Balance->setText("Current Balance : ");
    }

}

void balanceWindow::on_Bverify_clicked()
{
    if(ui->CBgetCard->currentText()!="Choose Card")
    {
        ui->GNumber->setText(ui->CBgetCard->currentText());
        ui->CBgetCard->setCurrentText("Choose Card");
    }
}
