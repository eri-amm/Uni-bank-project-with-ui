#include "signwindow.h"
#include "ui_signwindow.h"
#include "panelwindow.h"
#include "ui_panelwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <QFileDialog>
#include "common.h"
#include <iostream>
using namespace std;
QString picaddy;
signWindow::signWindow( QSqlDatabase &database,QSqlQuery &insertData,MainWindow *Loginpage,vector<transactions>&translist,vector<cards>& bank,vector <users>& account ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::signWindow)
{
    ui->setupUi(this);
    QWidget::setWindowIcon(QIcon(":/new/prefix1/elite - Copy.png"));
    QWidget::setWindowTitle("Elite Bank - Sign-Up");
    this->account = account;
    this->Loginpage=Loginpage;
    this->insertData=insertData;
    this->bank=bank;
    this->database=database;
    this->translist=translist;
    extern QString userin;
    extern int userind;
    extern QString welcome;
    setStyleSheet("signWindow {border-image: url(:/new/prefix1/Hig.jpg);}");
    QPixmap elite(":/new/prefix1/elite.png");
    auto logo=elite.scaled(450,300);
    ui->elite->setPixmap(logo);
    ui->GID->setPlaceholderText("ID Number");
    ui->GName->setPlaceholderText("First Name");
    ui->Gfamily->setPlaceholderText("Last Name");
    ui->GAge->setPlaceholderText("Age(years)");
    ui->GUser->setPlaceholderText("Username");
    ui->Gpass->setPlaceholderText("Password");
    ui->Bmakeacc->setIcon(QIcon(":/new/prefix1/add-contact.png"));
    ui->Bmakeacc->setStyleSheet("QPushButton {color:black;}""QPushButton:hover{color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(248, 24, 255, 255), stop:1 rgba(255, 47, 47, 255));}");
    ui->BaddPhoto->setStyleSheet("QPushButton {color:black;}""QPushButton:hover{color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));}");
    ui->Bmakeacc->setIconSize(QSize(40,40));
    ui->BaddPhoto->setIcon(QIcon(":/new/prefix1/picture.png"));
    ui->BaddPhoto->setIconSize(QSize(40,40));
    ui->Gpass->setEchoMode(QLineEdit::Password);
    ui->Bvisiable->setIcon(QIcon(":/new/prefix1/eye.png"));
    ui->Bvisiable->setIconSize(QSize(30,30));
    QGraphicsDropShadowEffect *frameShadow=new QGraphicsDropShadowEffect(ui->FsignUp);
        frameShadow->setBlurRadius(25.0);
        frameShadow->setColor(palette().color(QPalette::Shadow));
        frameShadow->setOffset(0.0);
        ui->FsignUp->setGraphicsEffect(frameShadow);
}

signWindow::~signWindow()
{
    delete ui;
}

void signWindow::on_Bmakeacc_clicked()
{
    QString name,family,user,pass,id;
    int age;
    name=ui->GName->text();
    age=ui->GAge->text().toInt();
    if(age<18)
    {
        ui->error->setText("You Must be Atleat 18 Years Old to Open an Account Under Your Name");
        return;
    }
    family=ui->Gfamily->text();
    id=ui->GID->text();
    if(id.length()!=10)
    {
        ui->error->setText("Incorrect ID Number");
        return;
    }
    for (int i=0;i<ui->GID->text().size();i++) {
        if(ui->GID->text()[i]>='A'&&ui->GID->text()[i]<='z')
        {
            ui->error->setText("ID Number Cannot Be Letters");
            return;
        }
    }
    if(ui->GName->text()=="")
    {
        ui->error->setText("FirstName Field Cannot be Empty");
        return;
    }

    if(ui->Gfamily->text()=="")
    {
        ui->error->setText("LastName Field Cannot be Empty");
        return;
    }
    if(ui->Gpass->text()=="")
    {
        ui->error->setText("Password Field Cannot be Empty");
        return;
    }
    if(ui->GAge->text()=="")
    {
        ui->error->setText("Age Field Cannot be Empty");
        return;
    }
    if(ui->GID->text()=="")
    {
        ui->error->setText("ID Number Field Cannot be Empty");
        return;
    }
    for(int i=0;i<ui->GUser->text().size();i++)
    if(ui->GUser->text()[i]==' ')
    {
        ui->error->setText("Username Cannot Have Any Spaces");
        return;
    }
    for(int i=0;i<ui->GUser->text().size();i++)
    if(ui->GUser->text()[i]=='-')
    {
        ui->error->setText("Username Cannot Have Any Dashes");
        return;
    }
    user=ui->GUser->text();
    for (int i=0;i<account.size();i++) {
        if(QString::fromStdString(account[i].getUsername())==user)
        {
            ui->error->setText("Username is Already Taken");
            return;
        }
    }
    pass=ui->Gpass->text();
    userin=user;
    users newUser;
    newUser.setId(id.toStdString());
    newUser.setAge(to_string(age));
    newUser.setPass(pass.toStdString());
    newUser.setFamily(family.toStdString());
    newUser.setUsername(user.toStdString());
    newUser.setName(name.toStdString());
    if(picaddy!="")newUser.setPic(picaddy.toStdString());
    account.push_back(newUser);
    userind=account.size()-1;
    insertData.prepare("INSERT INTO users(username,password,firstname,lastname,IdNum,age,picAddress) VALUES(:username,:password,:firstname,:lastname,:IdNum,:age,:picAddress)");
    insertData.bindValue(":username",QString::fromStdString(newUser.getUsername()));
            insertData.bindValue(":password",QString::fromStdString(newUser.getPass()));
            insertData.bindValue(":firstname",QString::fromStdString(newUser.getName()));
            insertData.bindValue(":lastname",QString::fromStdString(newUser.getFamily()));
            insertData.bindValue(":IdNum",QString::fromStdString(newUser.getId()));
            insertData.bindValue(":age",QString::fromStdString(newUser.getAge()));
            insertData.bindValue(":picAddress",QString::fromStdString(newUser.getPic()));
            insertData.exec();
            QSqlDatabase::database().commit();
   welcome="Hello, "+userin+"\n Welcome!";
    static panelWindow *panel=new panelWindow(database,insertData,translist,bank,account);
       panel->show();
       this->hide();
}
void signWindow::on_BLogin_clicked()
{
       Loginpage->show();
       this->hide();
}

void signWindow::on_BaddPhoto_clicked()
{
    picaddy=QFileDialog::getOpenFileName(this,tr("Please Choose A Photo: "),"",tr("JPG Only (*.JPG)"));
}

void signWindow::on_Bvisiable_clicked()
{
    if(ui->Gpass->echoMode()==QLineEdit::Password)
    {
        ui->Gpass->setEchoMode(QLineEdit::Normal);
        ui->Bvisiable->setIcon(QIcon(":/new/prefix1/show.png"));
    }
    else
    {
        ui->Gpass->setEchoMode(QLineEdit::Password);
        ui->Bvisiable->setIcon(QIcon(":/new/prefix1/eye.png"));
    }
ui->Bvisiable->setIconSize(QSize(30,30));
}
