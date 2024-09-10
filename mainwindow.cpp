#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signwindow.h"
#include "ui_signwindow.h"
#include <fstream>
#include "panelwindow.h"
#include "users.h"
#include "common.h"
#include "ui_panelwindow.h"
#include <QString>
#include "cards.h"
using namespace std;
 QString userin;
 int userind;
 QString welcome;
 std::string cardDeets[3][5];
MainWindow::MainWindow( QSqlDatabase &database,QSqlQuery &insertData,vector<transactions>&translist,vector<cards>& bank,vector<users>&account ,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowIcon(QIcon(":/new/prefix1/elite - Copy.png"));
    QWidget::setWindowTitle("Elite Bank - Login");
    this->account = account;
    this->bank=bank;
    this->insertData=insertData;
    this->database=database;
    this->translist=translist;
    ui->BLogin->setIcon(QIcon(":/new/prefix1/password.png"));
    ui->BLogin->setIconSize(QSize(50,50));
    QPixmap elite(":/new/prefix1/elite.png");
    auto logo=elite.scaled(450,300);
    ui->elite->setPixmap(logo);
    setStyleSheet("MainWindow {border-image: url(:/new/prefix1/Hig.jpg);}");
    ui->BLogin->setStyleSheet("QPushButton {color:black;}""QPushButton:hover{color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(248, 24, 255, 255), stop:1 rgba(255, 47, 47, 255));}");
    ui->GUser->setPlaceholderText("Username");
    ui->GPass->setPlaceholderText("Password");
    ui->GPass->setEchoMode(QLineEdit::Password);
    ui->Bvisiable->setIcon(QIcon(":/new/prefix1/eye.png"));
    ui->Bvisiable->setIconSize(QSize(30,30));
    QGraphicsDropShadowEffect *frameShadow=new QGraphicsDropShadowEffect(ui->FLogin);
        frameShadow->setBlurRadius(25.0);
        frameShadow->setColor(palette().color(QPalette::Shadow));
        frameShadow->setOffset(0.0);
    ui->FLogin->setGraphicsEffect(frameShadow);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_BLogin_clicked()
{
    userin=ui->GUser->text();
    QString passin=ui->GPass->text();
    int counter=0;
    if(userin!=""&&passin!="")
    for(int i=0;i<account.size();i++)
    {
        if(userin.toStdString()==account[i].getUsername())
            if(passin.toStdString()==account[i].getPass())
            {
                userind=i;
                for(int j=0;j<bank.size();j++)
                {
                    if(userin.toStdString()==bank[j].getUsername())
                    {
                    account[userind].getLl().push(bank[j]);
                    if(counter<3)
                        {
                        cardDeets[counter][0]="IR"+bank[j].getSHABA();
                        cardDeets[counter][1]=bank[j].getCard_number();
                        cardDeets[counter][2]=account[userind].getName()+"  "+account[userind].getFamily();
                        cardDeets[counter][3]=bank[j].getCvv2();
                        cardDeets[counter][4]=bank[j].getExpire_year();
                        counter++;
                        }
                    }
                }
                welcome="Hello, "+userin+"\n Welcome Back!";
                static panelWindow *panel=new panelWindow(this->database,this->insertData,translist,bank,account);
                panel->show();
                this->hide();
                break;
            }
    }
    ui->Error->setText("Username Or Password Is Wrong");
}

void MainWindow::on_BRegister_clicked()
{
    static signWindow *signup=new signWindow(this->database,this->insertData,this,translist,bank,account);
    signup->show();
    this->hide();
}


void MainWindow::on_Bvisiable_clicked()
{
    if(ui->GPass->echoMode()==QLineEdit::Password)
      {
          ui->GPass->setEchoMode(QLineEdit::Normal);
          ui->Bvisiable->setIcon(QIcon(":/new/prefix1/show.png"));
      }
      else
      {
          ui->GPass->setEchoMode(QLineEdit::Password);
          ui->Bvisiable->setIcon(QIcon(":/new/prefix1/eye.png"));
      }
  ui->Bvisiable->setIconSize(QSize(30,30));
}
