#include "passwindow.h"
#include "ui_passwindow.h"
#include "panelwindow.h"
#include "common.h"
#include "ui_panelwindow.h"
passWindow::passWindow( QSqlDatabase &database,QSqlQuery &insertData,panelWindow* panelPage,vector<transactions>&translist,vector<cards> &bank,vector<users>&account ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::passWindow)
{
    ui->setupUi(this);
    QWidget::setWindowIcon(QIcon(":/new/prefix1/elite - Copy.png"));
    QWidget::setWindowTitle("Elite Bank - Change Password");
    extern int userind;
    this->bank=bank;
    this->account=account;
    this->database=database;
    this->panelPage=panelPage;
    this->translist=translist;
    this->insertData=insertData;
    node<cards>*tmp=account[userind].getLl().get_head();
    while(tmp!=nullptr)
    {
      ui->CBgetCard->addItem(QString::fromStdString(tmp->get_data().getCard_number()));
      tmp=tmp->get_next();
    }
    ui->Bverify->setIcon(QIcon(":/new/prefix1/check.png"));
    ui->Bverify->setIconSize(QSize(33,33));
    ui->Bverify->setStyleSheet("QPushButton {border-radius:30px;margin: 0;background-color:white;}""QPushButton:hover{background-color:rgb(0,255,0);border-radius:30px;margin: 0;}");
    ui->CBgetCard->setStyleSheet("QComboBox {color:black;background-color:transparent;}""QComboBox:hover{border-radius:10px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));}");
    setStyleSheet("passWindow {background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:1, stop:0.284974 rgba(255, 37, 179, 255), stop:1 rgba(37, 243, 255, 255));};");
    ui->Gpre->setPlaceholderText("Previous Password");
    ui->Gnum->setPlaceholderText("Card Number");
    ui->Gnew->setPlaceholderText("New password");
    ui->comboBox->setStyleSheet("QComboBox {color:black;background-color:transparent;}""QComboBox:hover{border-radius:10px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));}");
    ui->Grenrew->setPlaceholderText("Confirm New Password");
    ui->BChange->setStyleSheet("QPushButton {color:black;background-color:transparent;}""QPushButton:hover{border-radius:15px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));}");
    ui->BChange->setIcon(QIcon(":/new/prefix1/reset-password.png"));
    ui->BChange->setIconSize(QSize(40,40));
    ui->Bback->setStyleSheet("QPushButton {color:black;background-color:transparent;}""QPushButton:hover{border-radius:15px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 11, 11, 255), stop:1 rgba(255, 81, 154, 255));}");
    ui->Bback->setIcon(QIcon(":/new/prefix1/return.png"));
    ui->Bback->setIconSize(QSize(40,50));
    ui->Grenrew->setEchoMode(QLineEdit::Password);
    ui->BvisiableCon->setIcon(QIcon(":/new/prefix1/eye.png"));
    ui->Gnew->setEchoMode(QLineEdit::Password);
    ui->BvisiableNew->setIcon(QIcon(":/new/prefix1/eye.png"));
    ui->Gpre->setEchoMode(QLineEdit::Password);
    ui->BvisiablePre->setIcon(QIcon(":/new/prefix1/eye.png"));
    ui->BvisiableCon->setIconSize(QSize(30,30));
    ui->BvisiableNew->setIconSize(QSize(30,30));
    ui->BvisiablePre->setIconSize(QSize(30,30));
}

passWindow::~passWindow()
{
    delete ui;
}
void passWindow::update_info(vector<cards>&bank,vector<users>&account)
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
void passWindow::on_Bback_clicked()
{
    panelPage->show();
    panelPage->fill_cards(bank,account);
       this->hide();
}

void passWindow::on_BChange_clicked()
{
    QString pre=ui->Gpre->text(),number=ui->Gnum->text();
      node<cards>* tmp=account[userind].getLl().get_head();
      //get card address
      while (tmp!=nullptr)
      {
          if(number.toStdString()==tmp->get_data().getCard_number())
          {
              break;
          }
          else tmp=tmp->get_next();
      }

      //check for card address error
      if(tmp==nullptr)
      {
          ui->error->setText("Card Number Does Not Match Any Card Info Owned By The User");
          return;
      }
      //check for tpye-box error
      else if(ui->comboBox->currentText()=="Password Type")
      {
          ui->error->setText("Invalid Password Type");

          return;
      }
      //check for password field errors
      else if(!(ui->Gnew->text()==ui->Grenrew->text()))
      {
          ui->error->setText("New Password Does Not Match The Confirmation Field");
          return;
      }
      for (int i=0;i<ui->Gnew->text().size();i++) {
          if(ui->Gnew->text()[i]>='A'&&ui->Gnew->text()[i]<='z')
          {
              ui->error->setText("Password Must Contain Only Digits");
              return;
          }
      }
      if(ui->Gnew->text().size()!=4)
      {
          ui->error->setText("Password Must Be Exactly 4 Digits");
          return;
      }
      else if(!((ui->comboBox->currentText()=="Card Password"&&tmp->get_data().getDefault_pass()==pre.toStdString())||(ui->comboBox->currentText()=="Default OUP"&&tmp->get_data().getDefault_OUP()==pre.toStdString())))
      {
          ui->error->setText("Previous Password Does Not Match Your Card Number(Or Selected Password Type)");
          return;
      }

      else//no errors
      {

          for (int i=0;i<bank.size();i++) {
              if((bank[i].getUsername()==tmp->get_data().getUsername())&&(bank[i].getCard_number()==tmp->get_data().getCard_number()))
              {
                  if(ui->comboBox->currentText().toStdString()=="Card Password")
                  {
                      bank[i].setDefault_pass(ui->Gnew->text().toStdString());
                      tmp->get_data().setDefault_pass(ui->Gnew->text().toStdString());
                      insertData.prepare("UPDATE cards SET cardPassword=:cardPassword WHERE cardNumber="+ui->Gnum->text());
                      insertData.bindValue(":cardPassword",ui->Gnew->text());
                      insertData.exec();
                      QSqlDatabase::database().commit();

                  }
                  else
                  {
                      bank[i].setDefault_OUP(ui->Gnew->text().toStdString());
                      tmp->get_data().setDefault_OUP(ui->Gnew->text().toStdString());
                      insertData.prepare("UPDATE cards SET defaultOUP=:defaultOUP WHERE cardNumber="+ui->Gnum->text());
                      insertData.bindValue(":defaultOUP",ui->Gnew->text());
                      insertData.exec();
                      QSqlDatabase::database().commit();
                  }
                  ui->error->setStyleSheet("color: rgb(0, 170, 0);");
                  ui->error->setText("Password Was Changed Sucsessfully");
                  return;
              }
          }
      }
}

void passWindow::on_BvisiablePre_clicked()
{
    if(ui->Gpre->echoMode()==QLineEdit::Password)
    {
        ui->Gpre->setEchoMode(QLineEdit::Normal);
        ui->BvisiablePre->setIcon(QIcon(":/new/prefix1/show.png"));
    }
    else
    {
        ui->Gpre->setEchoMode(QLineEdit::Password);
        ui->BvisiablePre->setIcon(QIcon(":/new/prefix1/eye.png"));
    }
ui->BvisiablePre->setIconSize(QSize(30,30));
}

void passWindow::on_BvisiableNew_clicked()
{
    if(ui->Gnew->echoMode()==QLineEdit::Password)
    {
        ui->Gnew->setEchoMode(QLineEdit::Normal);
        ui->BvisiableNew->setIcon(QIcon(":/new/prefix1/show.png"));
    }
    else
    {
        ui->Gnew->setEchoMode(QLineEdit::Password);
        ui->BvisiableNew->setIcon(QIcon(":/new/prefix1/eye.png"));
    }
ui->BvisiableNew->setIconSize(QSize(30,30));
}

void passWindow::on_BvisiableCon_clicked()
{
    if(ui->Grenrew->echoMode()==QLineEdit::Password)
    {
        ui->Grenrew->setEchoMode(QLineEdit::Normal);
        ui->BvisiableCon->setIcon(QIcon(":/new/prefix1/show.png"));
    }
    else
    {
        ui->Grenrew->setEchoMode(QLineEdit::Password);
        ui->BvisiableCon->setIcon(QIcon(":/new/prefix1/eye.png"));
    }
ui->BvisiableCon->setIconSize(QSize(30,30));
}

void passWindow::on_Bverify_clicked()
{
    if(ui->CBgetCard->currentText()!="Choose Card")
    {
        ui->Gnum->setText(ui->CBgetCard->currentText());
        ui->CBgetCard->setCurrentText("Choose Card");
    }
}
