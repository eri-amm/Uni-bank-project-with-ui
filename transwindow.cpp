#include "transwindow.h"
#include "ui_transwindow.h"
#include "panelwindow.h"
#include <ctime>
#include <time.h>
#include <QString>
#include "timess.h"
#include <sstream>
#include "common.h"
#include "ui_panelwindow.h"
QString pass;
transWindow::transWindow( QSqlDatabase &database,QSqlQuery &insertData,panelWindow* panelPage,vector<transactions>&translist,vector<cards> &bank,vector<users>&account ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::transWindow)
{
    ui->setupUi(this);
    QWidget::setWindowIcon(QIcon(":/new/prefix1/elite - Copy.png"));
    QWidget::setWindowTitle("Elite Bank - Transfer");
    extern int userind;
    this->panelPage=panelPage;
    this->database=database;
    this->insertData=insertData;
    node<cards>*tmp=account[userind].getLl().get_head();
    while(tmp!=nullptr)
    {
      ui->CBgetCard->addItem(QString::fromStdString(tmp->get_data().getCard_number()));
      tmp=tmp->get_next();
    }
    QPixmap arr("/Users/ASUS/Documents/untitled15/arrow.png");
    auto newpixmap=arr.scaled(53,53);
    ui->Bverify->setIcon(QIcon(":/new/prefix1/check.png"));
    ui->Bverify->setIconSize(QSize(33,33));
    ui->Bverify->setStyleSheet("QPushButton {border-radius:30px;margin: 0;background-color:white;}""QPushButton:hover{background-color:rgb(0,255,0);border-radius:30px;margin: 0;}");
    ui->CBgetCard->setStyleSheet("QComboBox {color:black;background-color:transparent;}""QComboBox:hover{border-radius:10px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));}");
    ui->arrow->setPixmap(newpixmap);
    ui->Bmessage->setIcon(QIcon("/Users/ASUS/Documents/untitled15/email.jpg"));
    ui->Bmessage->setToolTip("optional tooltip");
    ui->Bmessage->setIconSize(QSize(40,40));
    this->bank=bank;
    this->account=account;
    this->translist=translist;
    setStyleSheet("transWindow {background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:1, stop:0.284974 rgba(255, 37, 179, 255), stop:1 rgba(37, 243, 255, 255));};");
    ui->Gown->setPlaceholderText("Your Card Number");
    ui->Gother->setPlaceholderText("Destination Card Number");
    ui->Gstatic->setPlaceholderText("Default Password");
    ui->Gdynamic->setPlaceholderText("OTP");
    ui->Btransfer->setStyleSheet("QPushButton {color:black;background-color:transparent;}""QPushButton:hover{border-radius:15px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));}");
    ui->Btransfer->setIcon(QIcon(":/new/prefix1/transfer.png"));
    ui->Btransfer->setIconSize(QSize(40,40));
    ui->Bback->setStyleSheet("QPushButton {color:black;background-color:transparent;}""QPushButton:hover{border-radius:15px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 11, 11, 255), stop:1 rgba(255, 81, 154, 255));}");
    ui->Bback->setIcon(QIcon(":/new/prefix1/return.png"));
    ui->Bback->setIconSize(QSize(40,50));
    ui->Gstatic->setEchoMode(QLineEdit::Password);
    ui->BvisiableStat->setIcon(QIcon(":/new/prefix1/eye.png"));
    ui->Gdynamic->setEchoMode(QLineEdit::Password);
    ui->BvisiableDy->setIcon(QIcon(":/new/prefix1/eye.png"));
    ui->BvisiableDy->setIconSize(QSize(30,30));
    ui->BvisiableStat->setIconSize(QSize(30,30));
}
transWindow::~transWindow()
{
    delete ui;
}

void transWindow::on_Bback_clicked()
{
    panelPage->fill_transactions(translist,bank);
    panelPage->fill_cards(bank,account);
    panelPage->show();
       this->hide();
}

void transWindow::on_Bmessage_clicked()
{  std::stringstream ss;
    ss << std::hex << stol(timess::timepassed());
    std::string res ( ss.str() );
   pass=QString::fromStdString(res);
   ui->Gdynamic->setText(pass);
   ui->Error->setText("We Sent An OUP To Your Phone Number");
}
void transWindow::update_info(vector<cards>&bank,vector<users>&account)
{
    this->bank=bank;
    this->account=account;
    node<cards>*tmp=account[userind].getLl().get_head();
    ui->CBgetCard->clear();
    ui->CBgetCard->addItem("Choose Card");
    while(tmp!=nullptr)
    {
      ui->CBgetCard->addItem(QString::fromStdString(tmp->get_data().getCard_number()));
      tmp=tmp->get_next();
    }
}
void transWindow::on_Btransfer_clicked()
{
    //getting current date
    int Chour=timess::get_hour(timess::getCurrentTime());
    int Csec=timess::get_second(timess::getCurrentTime());
    int Cmin=timess::get_minute(timess::getCurrentTime());
    int Cdate[3];
    Cdate[0]=timess::get_year(timess::getCurrentTime());
    Cdate[1]=timess::getMonth(timess::getCurrentTime());
    Cdate[2]=timess::getDay(timess::getCurrentTime());
    QString own=ui->Gown->text(),other=ui->Gother->text();
    QString fname,lname;
    long fee=ui->Gamount->text().toLong()/100;

    //getting user index
    int ownind=-1;
    for (int k=0;k<bank.size();k++)
        if((own.toStdString()==bank[k].getCard_number())&&(bank[k].getUsername()==account[userind].getUsername()))
        {
            ownind=k;
            break;
        }

    //checking transfer limit renewal
    string Ldate=transactions::get_last_date(translist,ui->Gown->text().toStdString());
    if(Ldate!="-1")
        if(transactions::check_ability(Ldate,Cdate))
        {
            bank[ownind].setTranslimit(0);
        }

    //getting destination index
    int otherind=-1;
    for(int i=0;i<bank.size();i++)
        if(other==QString::fromStdString(bank[i].getCard_number()))
        {
            otherind=i;
            break;
        }
    //checking user card number
    if(ownind==-1)
    {
        ui->Error->setText("Card Number Does Not Match Any Card Info Owned By the User");
        ui->otherName->setText("");
        return;
    }
    //checking destination card number
    else if(otherind==-1)
    {
         ui->Error->setText("Destination Card Number Does Not Match Any Registered Card Info");
         ui->otherName->setText("");
         return;
    }
       //getting destination name
       for (int k=0;k<account.size();k++)
       {
            if(account[k].getUsername()==bank[otherind].getUsername())
            {
                lname=QString::fromStdString(account[k].getFamily());
                fname=QString::fromStdString(account[k].getName());
                break;
            }
        }

    //checking for errors
    //checking amount field
    if(ui->Gamount->text().toInt()==0)
    {
      ui->Error->setText("Amount Field Must Be Filled Correctly");
      ui->otherName->setText("");
      return;
    }
    //checking password
    else if((ui->Gdynamic->text()==""&&ui->Gstatic->text()=="")||(ui->Gdynamic->text()==""&&ui->Gstatic->text()!=QString::fromStdString(bank[ownind].getDefault_OUP()))||(ui->Gstatic->text()==""&&ui->Gdynamic->text()!=pass)||(ui->Gdynamic->text()!=""&&ui->Gstatic->text()!=""))//checking passwords
    {
        ui->Error->setText("Password Fields Must Be Filled Correctly");
        ui->otherName->setText("");
        return;
    }
    //checking transfer amount limit with default OUP
    else if((ui->Gdynamic->text()==""&&ui->Gstatic->text()==QString::fromStdString(bank[ownind].getDefault_OUP()))&&(ui->Gamount->text().toLongLong()>1000000))
    {
        ui->Error->setText("You Cannot Transfer More Than 1000000 At A Time With Default OUP");
        ui->otherName->setText("");
        return;
    }
    //checking account balance

    if(!((ui->Gamount->text().toLongLong()+fee)<=bank[ownind].getBalance()))
    {
        ui->Error->setText("Insuffcient Account Balance");
        ui->otherName->setText("");
        return;
    }
    //checking transfer limit
    else if((bank[ownind].getTranslimit())==60000000)
    {
        ui->Error->setText("You Have Reached Your Daily Transfer Limit For Today");
        ui->otherName->setText("");
        return;
    }
    else if(bank[ownind].getTranslimit()+ui->Gamount->text().toLongLong()>60000000)
    {
        ui->Error->setText("This Transaction Will Exceed The Daily Transfer Limit(Currently At "+QString::number(bank[ownind].getTranslimit())+" Rials )");
        ui->otherName->setText("");
        return;
    }
    //checking expiration date
    else if(!(timess::get_year(timess::getCurrentTime())<=stoi(bank[ownind].getExpire_year())))
    {
      ui->Error->setText("Your Card Has Been Expired");
      ui->otherName->setText("");
      return;
    }
    //checking amount limit
    else if(!(ui->Gamount->text().toLongLong()<=30000000))
    {
        ui->Error->setText("You Cannot Transfer More than 30 Million Rials At A Time");
        ui->otherName->setText("");
        return;
    }

    else// all fields are correct
    {
        long NewBalance=(bank[ownind].getBalance())-(ui->Gamount->text().toLongLong()+fee);
        long NewTransLimit=(bank[ownind].getTranslimit())+(ui->Gamount->text().toLongLong()+fee);
        bank[ownind].setBalance(NewBalance);
        bank[ownind].setTranslimit(bank[ownind].getTranslimit()+ui->Gamount->text().toLongLong());
        bank[otherind].setBalance(bank[otherind].getBalance()+ui->Gamount->text().toLongLong());
        node<cards>* tmp=account[userind].getLl().get_head();
        while(tmp!=nullptr)
        {
            if(bank[ownind].getCard_number()==tmp->get_data().getCard_number())
            {
                tmp->get_data().setBalance(bank[ownind].getBalance()-(ui->Gamount->text().toLongLong()+fee));
                tmp->get_data().setTranslimit(bank[ownind].getTranslimit()+ui->Gamount->text().toLongLong());
                break;
            }
            else(tmp=tmp->get_next());
        }
        ui->Error->setText("");
        ui->otherName->setText("Successful Transfer To "+fname+"  "+lname);
        transactions newAction;
        newAction.setOwnuser(userin.toStdString());
        newAction.setOwncard(ui->Gown->text().toStdString());
        newAction.setAmount(ui->Gamount->text().toLong());
        newAction.setOthercard(bank[otherind].getCard_number());
        newAction.setOthername(fname.toStdString());
        newAction.setDate(to_string(timess::get_year(timess::getCurrentTime()))+"/"+to_string(timess::getMonth(timess::getCurrentTime()))+"/"+to_string(timess::getDay(timess::getCurrentTime()))+" At "+to_string(Chour)+":"+to_string(Cmin)+":"+to_string(Csec));
        insertData.prepare("INSERT INTO transactions(username,OwnCardNumber,OtherCardNumber,amount,date,otherName) VALUES(:username,:OwnCardNumber,:OtherCardNumber,:amount,:date,:otherName)");
        insertData.bindValue(":username",QString::fromStdString(newAction.getOwnuser()));
        insertData.bindValue(":OwnCardNumber",QString::fromStdString(newAction.getOwncard()));
        insertData.bindValue(":amount",QString::number(newAction.getAmount()));
        insertData.bindValue(":OtherCardNumber",QString::fromStdString(newAction.getOthercard()));
        insertData.bindValue(":otherName",QString::fromStdString(newAction.getOthername()));
        insertData.bindValue(":date",QString::fromStdString(newAction.getDate()));
        insertData.exec();
        QSqlDatabase::database().commit();
        insertData.prepare("UPDATE cards SET balance=:balance,transLimit=:transLimit WHERE cardNumber="+ui->Gown->text());
        insertData.bindValue(":balance",QString::number(NewBalance));
        insertData.bindValue(":transLimit",QString::number(NewTransLimit));
        insertData.exec();
        QSqlDatabase::database().commit();
        insertData.prepare("UPDATE cards SET balance=:balance WHERE cardNumber="+ui->Gother->text());
        insertData.bindValue(":balance",(bank[otherind].getBalance()+ui->Gamount->text().toLong()));
        insertData.exec();
        QSqlDatabase::database().commit();
        translist.push_back(newAction);
        return;
    }
}

void transWindow::on_BvisiableDy_clicked()
{
    if(ui->Gdynamic->echoMode()==QLineEdit::Password)
    {
        ui->Gdynamic->setEchoMode(QLineEdit::Normal);
        ui->BvisiableDy->setIcon(QIcon(":/new/prefix1/show.png"));
    }
    else
    {
        ui->Gdynamic->setEchoMode(QLineEdit::Password);
        ui->BvisiableDy->setIcon(QIcon(":/new/prefix1/eye.png"));
    }
ui->BvisiableDy->setIconSize(QSize(30,30));
}

void transWindow::on_BvisiableStat_clicked()
{
    if(ui->Gstatic->echoMode()==QLineEdit::Password)
    {
        ui->Gstatic->setEchoMode(QLineEdit::Normal);
        ui->BvisiableStat->setIcon(QIcon(":/new/prefix1/show.png"));
    }
    else
    {
        ui->Gstatic->setEchoMode(QLineEdit::Password);
        ui->BvisiableStat->setIcon(QIcon(":/new/prefix1/eye.png"));
    }
ui->BvisiableStat->setIconSize(QSize(30,30));
}

void transWindow::on_Bverify_clicked()
{
    if(ui->CBgetCard->currentText()!="Choose Card")
    {
    ui->Gown->setText(ui->CBgetCard->currentText());
    ui->CBgetCard->setCurrentText("Choose Card");
    }
}
