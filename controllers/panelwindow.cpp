#include "panelwindow.h"
#include "ui_panelwindow.h"
#include "passwindow.h"
#include "ui_passwindow.h"
#include "makewindow.h"
#include "users.h"
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include "ui_makewindow.h"
#include "balancewindow.h"
#include "ui_balancewindow.h"
#include "transwindow.h"
#include "ui_transwindow.h"
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include "transactions.h"
#include "common.h"
#include <QGraphicsDropShadowEffect>
panelWindow::panelWindow( QSqlDatabase &database,QSqlQuery &insertData,vector<transactions>&translist,vector<cards> &bank,vector<users>&account ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::panelWindow)
{
    ui->setupUi(this);
    QWidget::setWindowIcon(QIcon(":/new/prefix1/elite - Copy.png"));
    QWidget::setWindowTitle("Elite Bank - Main Menu");
    this->account=account;
    this->insertData=insertData;
    this->bank=bank;
    this->translist=translist;
    this->database=database;
    extern QString welcome;
    extern QString userin;
    //setting user-based info
    long long total=0;
    string near_expire;
    int year=10000;
    int month=13;
    QPieSeries *series=new QPieSeries;
    for (int i=0;i<bank.size();i++) {
        if(account[userind].getUsername()==bank[i].getUsername())
        {string year_str; string month_str;
            total+=bank[i].getBalance();
            for(int q=0;q<bank[i].getExpire_year().size();q++)
            {
                if(bank[i].getExpire_year()[q]!='/')year_str+=bank[i].getExpire_year()[q];
                else break;
            }
            for (int c=5;c<bank[i].getExpire_year().size();c++) {
                month_str+=bank[i].getExpire_year()[c];
            }
            if((year>stoi(year_str))||((year==stoi(year_str))&&(month>stoi(month_str))))
            {
                near_expire=bank[i].getExpire_year();
                year=stoi(year_str);
                month=stoi(month_str);
            }
            series->append(QString::number(stoll(bank[i].getAcc_number())%100000),bank[i].getBalance());
        }
    }
    ui->balance->setText("  "+QString::number(total)+" Rials");
    if(year!=10000)ui->expire->setText("           "+QString::fromStdString(near_expire));
    else ui->expire->setText("3 Years In The Future!");
    extern std::string cardDeets[3][5];
    QPixmap elite(":/new/prefix1/elite.png");
    auto logo=elite.scaled(85,50);
    //setting card info
    ui->CBcardDisplay->setStyleSheet("QComboBox {color:black;background-color:transparent;}""QComboBox:hover{border-radius:10px;color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));}");
    node<cards>*tmp=account[userind].getLl().get_head();
    while(tmp!=nullptr)
    {
      ui->CBcardDisplay->addItem(QString::fromStdString(tmp->get_data().getAcc_number()));
      tmp=tmp->get_next();
    }
    if(cardDeets[0][0]!="")
    {
        ui->accnum1->setText(QString::fromStdString(cardDeets[0][0]));
        ui->cardnum1->setText("            "+QString::fromStdString(cardDeets[0][1]));
        ui->name1->setText("               "+QString::fromStdString(cardDeets[0][2]));
        ui->cv1->setText(QString::fromStdString(cardDeets[0][3]));
        ui->expire1->setText(QString::fromStdString(cardDeets[0][4]));
        ui->card1->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(248, 24, 255, 255), stop:1 rgba(255, 47, 47, 255));"
                                "border-radius: 15px;" );
        ui->whole1_1->setStyleSheet("background-color:transparent;");
        ui->elite1->setPixmap(logo);
    }

    if(cardDeets[1][0]!="")
    {
        ui->accnum2->setText(QString::fromStdString(cardDeets[1][0]));
        ui->cardnum2->setText("            "+QString::fromStdString(cardDeets[1][1]));
        ui->name2->setText("               "+QString::fromStdString(cardDeets[1][2]));
        ui->cv2->setText(QString::fromStdString(cardDeets[1][3]));
        ui->expire2->setText(QString::fromStdString(cardDeets[1][4]));
        ui->card2->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));"
                                "border-radius: 15px;" );
        ui->whole2->setStyleSheet("background-color:transparent;");
        ui->elite2->setPixmap(logo);
    }

    if(cardDeets[2][0]!="")
    {
        ui->accnum3->setText(QString::fromStdString(cardDeets[2][0]));
        ui->cardnum3->setText("            "+QString::fromStdString(cardDeets[2][1]));
        ui->name3->setText("               "+QString::fromStdString(cardDeets[2][2]));
        ui->cv3->setText(QString::fromStdString(cardDeets[2][3]));
        ui->expire3->setText(QString::fromStdString(cardDeets[2][4]));
        ui->card3->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(200, 28, 166, 255), stop:1 rgba(55, 60, 255, 255));"
                                "border-radius: 15px;" );
        ui->whole3->setStyleSheet("background-color:transparent;");
        ui->elite->setPixmap(logo);
    }

    for (int i=0;i<translist.size();i++)
    {
        if(translist[i].getOwnuser()==account[userind].getUsername())
        {
            if(ui->trans1->text()=="")
            {
                ui->trans1->setText("To  "+QString::fromStdString(translist[i].getOthername())+"  "+QString::number(translist[i].getAmount())+" Rials"+"  "+QString::fromStdString(translist[i].getDate()));
                continue;
            }
            if(ui->trans2->text()=="")
            {
                ui->trans2->setText("To  "+QString::fromStdString(translist[i].getOthername())+"  "+QString::number(translist[i].getAmount())+" Rials"+"  "+QString::fromStdString(translist[i].getDate()));
                continue;
            }
            if(ui->trans3->text()=="")
            {
                ui->trans3->setText("To  "+QString::fromStdString(translist[i].getOthername())+"  "+QString::number(translist[i].getAmount())+" Rials"+"  "+QString::fromStdString(translist[i].getDate()));
                continue;
            }
            if(ui->trans4->text()=="")
            {
                ui->trans4->setText("To  "+QString::fromStdString(translist[i].getOthername())+"  "+QString::number(translist[i].getAmount())+" Rials"+"  "+QString::fromStdString(translist[i].getDate()));
                continue;
            }
            if(ui->trans5->text()=="")
            {
                ui->trans5->setText("To  "+QString::fromStdString(translist[i].getOthername())+"  "+QString::number(translist[i].getAmount())+" Rials"+"  "+QString::fromStdString(translist[i].getDate()));
                continue;
            }
        }
    }
    setStyleSheet("panelWindow {background-color: qlineargradient(spread:pad, x1:0.057, y1:0.0511364, x2:0.596, y2:0.739, stop:0 rgba(46, 179, 161, 255), stop:1 rgba(250, 96, 255, 255));}");
    ui->welcome->setText(welcome);
    QChart* chart=new QChart;
    chart->addSeries(series);
    chart->resize(360,360);
    QChartView *chartview=new QChartView(chart);
    chartview->setParent(ui->frame_12);
    //setting icons
    ui->get_Display->setIcon(QIcon(":/new/prefix1/check.png"));
    ui->get_Display->setIconSize(QSize(33,33));
    ui->Newacc->setIcon(QIcon(":/new/prefix1/bank-account.png"));
    ui->Newacc->setIconSize(QSize(40,40));
    ui->Exit->setIcon(QIcon(":/new/prefix1/log-out.png"));
    ui->Exit->setIconSize(QSize(33,33));
    ui->Balance->setIcon(QIcon(":/new/prefix1/wallet.png"));
    ui->Balance->setIconSize(QSize(40,40));
    ui->Transaction->setIcon(QIcon(":/new/prefix1/transfer-money.png"));
    ui->Transaction->setIconSize(QSize(40,40));
    ui->Changpass->setIcon(QIcon(":/new/prefix1/padlock.png"));
    ui->Changpass->setIconSize(QSize(40,40));
    ui->setpic->setIcon(QIcon(":/new/prefix1/picture.png"));
    ui->setpic->setIconSize(QSize(45,45));
    //setting button stylesheets
    ui->get_Display->setStyleSheet("QPushButton {border-radius:30px;margin: 0;background-color:white;}""QPushButton:hover{background-color:rgb(0,255,0);border-radius:30px;margin: 0;}");
    ui->Exit->setStyleSheet("QPushButton {border-radius:30px;margin: 0;background-color:white;}""QPushButton:hover{background-color:rgb(255,0,0);border-radius:30px;margin: 0;}");
    ui->Newacc->setStyleSheet("QPushButton {color:black;}""QPushButton:hover{color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.279793 rgba(48, 255, 77, 255), stop:1 rgba(71, 252, 255, 255));}");
    ui->Changpass->setStyleSheet("QPushButton {color:black;}""QPushButton:hover{color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));}");
    ui->Transaction->setStyleSheet("QPushButton {color:black;}""QPushButton:hover{color:black;background-color: qlineargradient(spread:pad, x1:0.073, y1:0.204545, x2:1, y2:1, stop:0 rgba(16, 255, 251, 255), stop:1 rgba(175, 255, 42, 255));}");
    ui->Balance->setStyleSheet("QPushButton {color:black;}""QPushButton:hover{color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.34715 rgba(229, 228, 0, 255), stop:0.766839 rgba(0, 255, 35, 255));}");
    ui->setpic->setStyleSheet("QPushButton {color:black;}""QPushButton:hover{color:black;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 203, 34, 255), stop:1 rgba(241, 42, 255, 255));}");
    QPixmap arr(QString::fromStdString(account[userind].getPic()));
    auto newpixmap=arr.scaled(77,77);
    ui->pic->setPixmap(newpixmap);
    //making frame shadows
    QGraphicsDropShadowEffect *frameShadow=new QGraphicsDropShadowEffect(ui->left_frame);
        frameShadow->setBlurRadius(25.0);
        frameShadow->setColor(palette().color(QPalette::Shadow));
        frameShadow->setOffset(0.0);
    QGraphicsDropShadowEffect *whitesShadow=new QGraphicsDropShadowEffect(ui->left_frame);
        whitesShadow->setBlurRadius(33.0);
        whitesShadow->setColor(palette().color(QPalette::Shadow));
        whitesShadow->setOffset(0.0);
    QGraphicsDropShadowEffect *blacksShadow=new QGraphicsDropShadowEffect(ui->left_frame);
        blacksShadow->setBlurRadius(25.0);
        blacksShadow->setColor(palette().color(QPalette::Shadow));
        blacksShadow->setOffset(0.0);
    QGraphicsDropShadowEffect *card1Shadow=new QGraphicsDropShadowEffect(ui->left_frame);
        card1Shadow->setBlurRadius(15.0);
        card1Shadow->setColor(palette().color(QPalette::Shadow));
        card1Shadow->setOffset(0.0);
     QGraphicsDropShadowEffect *card2Shadow=new QGraphicsDropShadowEffect(ui->left_frame);
        card2Shadow->setBlurRadius(15.0);
        card2Shadow->setColor(palette().color(QPalette::Shadow));
        card2Shadow->setOffset(0.0);
     QGraphicsDropShadowEffect *card3Shadow=new QGraphicsDropShadowEffect(ui->left_frame);
        card3Shadow->setBlurRadius(15.0);
        card3Shadow->setColor(palette().color(QPalette::Shadow));
        card3Shadow->setOffset(0.0);
     //setting frame shadows
     ui->left_frame->setGraphicsEffect(frameShadow);
     ui->whites->setGraphicsEffect(whitesShadow);
     ui->blacks->setGraphicsEffect(blacksShadow);
     ui->card1->setGraphicsEffect(card1Shadow);
     ui->card2->setGraphicsEffect(card2Shadow);
     ui->card3->setGraphicsEffect(card3Shadow);
}
void panelWindow::fill_cards(vector<cards>&bank,vector<users>&account)
{
    this->bank=bank;
    this->account=account;
    int year=10000;
    QPieSeries *series=new QPieSeries;
    int month=13;
    QPixmap elite(":/new/prefix1/elite.png");
    auto logo=elite.scaled(85,50);
    long long total=0;
    string near_expire;
    for (int i=0;i<bank.size();i++) {
        if(account[userind].getUsername()==bank[i].getUsername())
        {string year_str; string month_str;
            total+=bank[i].getBalance();
            for(int q=0;q<bank[i].getExpire_year().size();q++)
            {
                if(bank[i].getExpire_year()[q]!='/')year_str+=bank[i].getExpire_year()[q];
                else break;
            }
            for (int c=5;c<bank[i].getExpire_year().size();c++) {
                month_str+=bank[i].getExpire_year()[c];
            }
            if((year>stoi(year_str))||((year==stoi(year_str))&&(month>stoi(month_str))))
            {
                near_expire=bank[i].getExpire_year();
                year=stoi(year_str);
                month=stoi(month_str);
            }
            series->append(QString::number(stoll(bank[i].getAcc_number())%100000),bank[i].getBalance());
        }
    }
    ui->balance->setText("  "+QString::number(total)+" Rials");
    if(year!=10000)ui->expire->setText("           "+QString::fromStdString(near_expire));
    else ui->expire->setText("3 Years In The Future!");
    QChart* chart=new QChart;
    chart->addSeries(series);
    chart->resize(360,360);
    QChartView *chartview=new QChartView(chart);
    chartview->setParent(ui->frame_12);
    node<cards>* tmp=account[userind].getLl().get_head();
    ui->CBcardDisplay->clear();
    ui->CBcardDisplay->addItem("Display Card");
    while(tmp!=nullptr)
    {
      ui->CBcardDisplay->addItem(QString::fromStdString(tmp->get_data().getAcc_number()));
      tmp=tmp->get_next();
    }
    if(cardDeets[0][0]!="")
    {
        ui->accnum1->setText(QString::fromStdString(cardDeets[0][0]));
        ui->cardnum1->setText("            "+QString::fromStdString(cardDeets[0][1]));
        ui->name1->setText("               "+QString::fromStdString(cardDeets[0][2]));
        ui->cv1->setText(QString::fromStdString(cardDeets[0][3]));
        ui->expire1->setText(QString::fromStdString(cardDeets[0][4]));
        ui->card1->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(248, 24, 255, 255), stop:1 rgba(255, 47, 47, 255));"
                                "border-radius: 15px;" );
        ui->whole1_1->setStyleSheet("background-color:transparent;");
        ui->elite1->setPixmap(logo);
    }

    if(cardDeets[1][0]!="")
    {
        ui->accnum2->setText(QString::fromStdString(cardDeets[1][0]));
        ui->cardnum2->setText("            "+QString::fromStdString(cardDeets[1][1]));
        ui->name2->setText("               "+QString::fromStdString(cardDeets[1][2]));
        ui->cv2->setText(QString::fromStdString(cardDeets[1][3]));
        ui->expire2->setText(QString::fromStdString(cardDeets[1][4]));
        ui->card2->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 128, 236, 255), stop:1 rgba(60, 237, 255, 255));"
                                "border-radius: 15px;" );
        ui->whole2->setStyleSheet("background-color:transparent;");
        ui->elite2->setPixmap(logo);
    }

    if(cardDeets[2][0]!="")
    {
        ui->accnum3->setText(QString::fromStdString(cardDeets[2][0]));
        ui->cardnum3->setText("            "+QString::fromStdString(cardDeets[2][1]));
        ui->name3->setText("               "+QString::fromStdString(cardDeets[2][2]));
        ui->cv3->setText(QString::fromStdString(cardDeets[2][3]));
        ui->expire3->setText(QString::fromStdString(cardDeets[2][4]));
        ui->card3->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(200, 28, 166, 255), stop:1 rgba(55, 60, 255, 255));"
                                "border-radius: 15px;" );
        ui->whole3->setStyleSheet("background-color:transparent;");
        ui->elite->setPixmap(logo);
    }

}
void panelWindow::fill_transactions(vector<transactions>&translist,vector<cards>&bank)
{
    this->translist=translist;
    this->bank=bank;
    long long total=0;
    for (int i=0;i<bank.size();i++)
        if(account[userind].getUsername()==bank[i].getUsername())
            total+=bank[i].getBalance();
    ui->balance->setText("  "+QString::number(total)+" Rials");

    for (int i=0;i<translist.size();i++)
    {
        if(translist[i].getOwnuser()==account[userind].getUsername())
        {
            if(ui->trans1->text()=="")
            {
                ui->trans1->setText("To  "+QString::fromStdString(translist[i].getOthername())+"  "+QString::number(translist[i].getAmount())+" Rials"+"  "+QString::fromStdString(translist[i].getDate()));
                continue;
            }
            if(ui->trans2->text()=="")
            {
                ui->trans2->setText("To  "+QString::fromStdString(translist[i].getOthername())+"  "+QString::number(translist[i].getAmount())+" Rials"+"  "+QString::fromStdString(translist[i].getDate()));
                continue;
            }
            if(ui->trans3->text()=="")
            {
                ui->trans3->setText("To  "+QString::fromStdString(translist[i].getOthername())+"  "+QString::number(translist[i].getAmount())+" Rials"+"  "+QString::fromStdString(translist[i].getDate()));
                continue;
            }
            if(ui->trans4->text()=="")
            {
                ui->trans4->setText("To  "+QString::fromStdString(translist[i].getOthername())+"  "+QString::number(translist[i].getAmount())+" Rials"+"  "+QString::fromStdString(translist[i].getDate()));
                continue;
            }
            if(ui->trans5->text()=="")
            {
                ui->trans5->setText("To  "+QString::fromStdString(translist[i].getOthername())+"  "+QString::number(translist[i].getAmount())+" Rials"+"  "+QString::fromStdString(translist[i].getDate()));
                continue;
            }
        }
    }

}
panelWindow::~panelWindow()
{
    delete ui;
}

void panelWindow::on_Transaction_clicked()
{
    static transWindow *transfer=new transWindow(this->database,this->insertData,this,translist,bank,account);
    transfer->update_info(bank,account);
    transfer->show();
    this->hide();
}

void panelWindow::on_Newacc_clicked()
{
    static MakeWindow *newacc=new MakeWindow(this->database,this->insertData,this,translist,bank,account);
    newacc->show();
    this->hide();
}

void panelWindow::on_Balance_clicked()
{
    static balanceWindow *balance=new balanceWindow(this,translist,bank,account);
    balance->update_info(bank,account);
    balance->show();
    this->hide();
}

void panelWindow::on_Changpass_clicked()
{
    static passWindow *pass=new passWindow(this->database,this->insertData,this,translist,bank,account);
    pass->update_info(bank,account);
    pass->show();
    this->hide();
}

void panelWindow::on_Exit_clicked()
{
    QCoreApplication::quit();
}

void panelWindow::on_setpic_clicked()
{
    account[userind].setPic((QFileDialog::getOpenFileName(this,tr("Please Choose A Photo: "),"",tr("JPG Only (*.JPG)"))).toStdString());
    QPixmap arr(QString::fromStdString(account[userind].getPic()));
    auto newpixmap=arr.scaled(77,77);
    ui->pic->setPixmap(newpixmap);
    QString ey='\''+QString::fromStdString(account[userind].getId())+'\'';
    insertData.prepare("UPDATE users SET picAddress=:picAddress WHERE IdNum="+ey);
    QString hey=QString::fromStdString(account[userind].getPic());
    insertData.bindValue(":picAddress",hey);
    insertData.exec();
    QSqlDatabase::database().commit();
    //asd
}

void panelWindow::on_BCpink_clicked()
{
    setStyleSheet("panelWindow {background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(248, 24, 255, 255), stop:1 rgba(255, 47, 47, 255));}");
}

void panelWindow::on_BCgreen_clicked()
{
    setStyleSheet("panelWindow {background-color: qlineargradient(spread:pad, x1:0.073, y1:0.204545, x2:1, y2:1, stop:0 rgba(16, 255, 251, 255), stop:1 rgba(175, 255, 42, 255));}");
}

void panelWindow::on_BCdefault_clicked()
{
    setStyleSheet("panelWindow {background-color: qlineargradient(spread:pad, x1:0.057, y1:0.0511364, x2:0.596, y2:0.739, stop:0 rgba(46, 179, 161, 255), stop:1 rgba(250, 96, 255, 255));}");
}

void panelWindow::on_get_Display_clicked()
{
    if(ui->CBcardDisplay->currentText()!="Display Card")
    {
        node<cards>*tmp=account[userind].getLl().get_head();
        while(tmp!=nullptr)
        {
          if(tmp->get_data().getAcc_number()==ui->CBcardDisplay->currentText().toStdString())break;
          tmp=tmp->get_next();
        }
        ui->accnum3->setText("IR"+QString::fromStdString(tmp->get_data().getSHABA()));
        ui->cardnum3->setText("            "+QString::fromStdString(tmp->get_data().getCard_number()));
        ui->cv3->setText(QString::fromStdString(tmp->get_data().getCvv2()));
        ui->name3->setText("               "+QString::fromStdString(account[userind].getName()+"  "+account[userind].getFamily()));
        ui->expire3->setText(QString::fromStdString(tmp->get_data().getExpire_year()));
        ui->card3->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(200, 28, 166, 255), stop:1 rgba(55, 60, 255, 255));"
                                "border-radius: 15px;" );
        ui->whole3->setStyleSheet("background-color:transparent;");
    }
}
