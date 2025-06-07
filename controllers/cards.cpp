#include "cards.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <fstream>
#include "timess.h"
#include <QtSql>
#include <QSqlDatabase>
string cards::getLimitTime() const
{
    return limitTime;
}

void cards::setLimitTime(const string &value)
{
    limitTime = value;
}

cards::cards()
{
    expire_year=to_string(timess::get_year(timess::getCurrentTime())+3)+"/"+to_string(timess::getMonth(timess::getCurrentTime()));
    card_number="992648"+timess::timepassed();
    acc_number=timess::timepassed();
    SHABA="100000000"+timess::timepassed();
    cvv2= to_string((rand() % 9000) + 1000);
    translimit=0;
}
string cards::getUsername() const
{
    return username;
}

void cards::setUsername(const string &value)
{
    username = value;
}

string cards::getType() const
{
    return type;
}

void cards::setType(const string &value)
{
    type = value;
}

string cards::getCard_number() const
{
    return card_number;
}

void cards::setCard_number(const string &value)
{
    card_number = value;
}

string cards::getSHABA() const
{
    return SHABA;
}

void cards::setSHABA(const string &value)
{
    SHABA = value;
}

string cards::getAcc_number() const
{
    return acc_number;
}

void cards::setAcc_number(const string &value)
{
    acc_number = value;
}

string cards::getCvv2() const
{
    return cvv2;
}

void cards::setCvv2(const string &value)
{
    cvv2 = value;
}

long long cards::getBalance() const
{
    return balance;
}

void cards::setBalance(const long long &value)
{
    balance = value;
}

string cards::getExpire_year() const
{
    return expire_year;
}

void cards::setExpire_year(const string &value)
{
    expire_year = value;
}

string cards::getDefault_pass() const
{
    return default_pass;
}

void cards::setDefault_pass(string value)
{
    default_pass = value;
}

string cards::getDefault_OUP() const
{
    return default_OUP;
}

void cards::setDefault_OUP(string value)
{
    default_OUP = value;
}

long cards::getTranslimit() const
{
    return translimit;
}

void cards::setTranslimit(long value)
{
    translimit = value;
}

string cards::getOUP() const
{
    return OUP;
}

void cards::setOUP(const string &value)
{
    OUP = value;
}
void cards::cards_fill(vector<cards> &bank,QSqlQuery &insertData)
{
    cards newCard;
    insertData.prepare("SELECT * FROM cards");
    if(insertData.exec())
     while(insertData.next())
     {
         newCard.username=insertData.value("username").toString().toStdString();
         newCard.type=insertData.value("accountType").toString().toStdString();
         newCard.acc_number=insertData.value("accountNumber").toString().toStdString();
         newCard.balance=insertData.value("balance").toLongLong();
         newCard.default_pass=insertData.value("cardPassword").toString().toStdString();
         newCard.expire_year=insertData.value("expirationDate").toString().toStdString();
         newCard.default_OUP=insertData.value("defaultOUP").toString().toStdString();
         newCard.SHABA=insertData.value("SHABA").toString().toStdString();
         newCard.card_number=insertData.value("cardNumber").toString().toStdString();
         newCard.cvv2=insertData.value("cvv2").toString().toStdString();
         newCard.translimit=insertData.value("transLimit").toLongLong();
         bank.push_back(newCard);
     }
}

