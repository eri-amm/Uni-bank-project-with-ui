#include "makewindow.h"
#include "ui_makewindow.h"
#include "panelwindow.h"
#include "ui_panelwindow.h"
#include <fstream>
#include "cards.h"
#include "users.h"
#include "common.h"
MakeWindow::MakeWindow( QSqlDatabase &database,QSqlQuery &insertData,panelWindow* panelPage,vector<transactions>&translist,vector<cards> &bank,vector<users>&account ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MakeWindow)
{
    ui->setupUi(this);
    QWidget::setWindowIcon(QIcon(":/new/prefix1/elite - Copy.png"));
    QWidget::setWindowTitle("Elite Bank - Open Account");
    extern int userind;
    extern QString userin;
    this->panelPage=panelPage;
    this->database=database;
    this->bank=bank;
    this->insertData=insertData;
    this->account=account;
    this->translist=translist;
    extern std::string cardDeets[3][5];
    ui->Bmakeacc->setStyleSheet("QPushButton {color:black;background-color:transparent;}""QPushButton:hover{border-radius:15px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));}");
    ui->Bmakeacc->setIcon(QIcon(":/new/prefix1/bank-account (1).png"));
    ui->Bmakeacc->setIconSize(QSize(40,40));
    ui->typebox->setStyleSheet("QComboBox {color:black;background-color:transparent;}""QComboBox:hover{border-radius:10px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));}");
    ui->Bback->setStyleSheet("QPushButton {color:black;background-color:transparent;}""QPushButton:hover{border-radius:15px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 11, 11, 255), stop:1 rgba(255, 81, 154, 255));}");
    ui->Bback->setIcon(QIcon(":/new/prefix1/return.png"));
    ui->Bback->setIconSize(QSize(40,50));
    setStyleSheet("MakeWindow {background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:1, stop:0.284974 rgba(255, 37, 179, 255), stop:1 rgba(37, 243, 255, 255));};");
    ui->Gamount->setPlaceholderText("Starting amount(Rials)");
    ui->Gtwodigit->setPlaceholderText("Default OUP(optional)");
    ui->Gtwodigit->setEchoMode(QLineEdit::Password);
    ui->Gfourdigit->setPlaceholderText("Card Password");
    ui->Gfourdigit->setEchoMode(QLineEdit::Password);
    ui->BvisiableDef->setIcon(QIcon(":/new/prefix1/eye.png"));
    ui->Gtwodigit->setEchoMode(QLineEdit::Password);
    ui->BvisiableOUP->setIcon(QIcon(":/new/prefix1/eye.png"));
    ui->BvisiableDef->setIconSize(QSize(30,30));
    ui->BvisiableOUP->setIconSize(QSize(30,30));
}

MakeWindow::~MakeWindow()
{
    delete ui;
}

void MakeWindow::on_Bback_clicked()
{   panelPage->fill_cards(bank,account);
    panelPage->show();
       this->hide();
}

void MakeWindow::on_Bmakeacc_clicked()
{

    if(account[userind].getLl().get_size()==5)
    {
        ui->error->setText("You Can Only Have Up To 5 Cards At A Time");
        return;
    }
    else if((ui->Gamount->text().toInt()==0)||(ui->Gamount->text().toLong()<500000))
    {
        ui->error->setText("Starting amount Must Be Atleast 500000 Rials");
        return;
    }
    else if((ui->Gfourdigit->text().toInt()==0)||(ui->Gfourdigit->text().size()!=4))
    {
        ui->error->setText("Card Password Must Be Exactly 4 Digits");
        return;
    }
    else if(ui->Gtwodigit->text()!=""&&ui->Gtwodigit->text().size()!=4)
    {
        ui->error->setText("Defaault OUP Must Be Exactly 4 Digits");
        return;
    }
    for (int i=0;i<ui->Gtwodigit->text().size();i++) {
        if(ui->Gtwodigit->text()[i]>='A'&&ui->Gtwodigit->text()[i]<='z')
        {
            ui->error->setText("Card Password Cannot Be Letters");
            return;
        }
    }
    if(ui->typebox->currentText()=="Account Type")
    {
        ui->error->setText("please select an account type");
        return;
    }
    else{
        cards card;
        card.setType(ui->typebox->currentText().toStdString());
        card.setDefault_pass(ui->Gfourdigit->text().toStdString());
        card.setBalance(ui->Gamount->text().toLongLong());
        card.setDefault_OUP(ui->Gtwodigit->text().toStdString());
        card.setUsername(userin.toStdString());
        insertData.prepare("INSERT INTO cards(username,accountType,accountNumber,balance,cardPassword,expirationDate,defaultOUP,SHABA,cardNumber,cvv2) VALUES(:username,:accountType,:accountNumber,:balance,:cardPassword,:expirationDate,:defaultOUP,:SHABA,:cardNumber,:cvv2)");
        insertData.bindValue(":username",QString::fromStdString(card.getUsername()));
        insertData.bindValue(":accountType",QString::fromStdString(card.getType()));
        insertData.bindValue(":accountNumber",QString::fromStdString(card.getAcc_number()));
        insertData.bindValue(":balance",QString::number(card.getBalance()));
        insertData.bindValue(":cardPassword",QString::fromStdString(card.getDefault_pass()));
        insertData.bindValue(":expirationDate",QString::fromStdString(card.getExpire_year()));
        insertData.bindValue(":defaultOUP",QString::fromStdString(card.getDefault_OUP()));
        insertData.bindValue(":SHABA",QString::fromStdString(card.getSHABA()));
        insertData.bindValue(":cardNumber",QString::fromStdString(card.getCard_number()));
        QString hey=QString::fromStdString(card.getCvv2());
        if(cardDeets[0][0]=="")
        {
            cardDeets[0][0]="IR"+card.getSHABA();
            cardDeets[0][1]=card.getCard_number();
            cardDeets[0][2]=account[userind].getName()+"  "+account[userind].getFamily();
            cardDeets[0][3]=card.getCvv2();
            cardDeets[0][4]=card.getExpire_year();
        }
        else if(cardDeets[1][0]=="")
        {
            cardDeets[1][0]="IR"+card.getSHABA();
            cardDeets[1][1]=card.getCard_number();
            cardDeets[1][2]=account[userind].getName()+"  "+account[userind].getFamily();
            cardDeets[1][3]=card.getCvv2();
            cardDeets[1][4]=card.getExpire_year();
        }
        else if(cardDeets[2][0]=="")
        {
            cardDeets[2][0]="IR"+card.getSHABA();
            cardDeets[2][1]=card.getCard_number();
            cardDeets[2][2]=account[userind].getName()+"  "+account[userind].getFamily();
            cardDeets[2][3]=card.getCvv2();
            cardDeets[2][4]=card.getExpire_year();
        }
        insertData.bindValue(":cvv2",QString::fromStdString(card.getCvv2()));
        insertData.exec();
        QSqlDatabase::database().commit();
        account[userind].getLl().push(card);
        bank.push_back(card);
        ui->error->setStyleSheet("color: rgb(0, 170, 0);");
        ui->error->setText("Account Created Successfully");
    }
}

void MakeWindow::on_BvisiableOUP_clicked()
{
    if(ui->Gtwodigit->echoMode()==QLineEdit::Password)
    {
        ui->Gtwodigit->setEchoMode(QLineEdit::Normal);
        ui->BvisiableOUP->setIcon(QIcon(":/new/prefix1/show.png"));
    }
    else
    {
        ui->Gtwodigit->setEchoMode(QLineEdit::Password);
        ui->BvisiableOUP->setIcon(QIcon(":/new/prefix1/eye.png"));
    }
ui->BvisiableOUP->setIconSize(QSize(30,30));
}

void MakeWindow::on_BvisiableDef_clicked()
{
    if(ui->Gfourdigit->echoMode()==QLineEdit::Password)
    {
        ui->Gfourdigit->setEchoMode(QLineEdit::Normal);
        ui->BvisiableDef->setIcon(QIcon(":/new/prefix1/show.png"));
    }
    else
    {
        ui->Gfourdigit->setEchoMode(QLineEdit::Password);
        ui->BvisiableDef->setIcon(QIcon(":/new/prefix1/eye.png"));
    }
ui->BvisiableDef->setIconSize(QSize(30,30));
}
