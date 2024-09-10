#include "transactions.h"
#include <fstream>
#include <QtSql>
#include <qsqldatabase.h>
#include <vector>
transactions::transactions()
{

}
long long transactions::getAmount() const
{
    return amount;
}

void transactions::setAmount(const long long &value)
{
    amount = value;
}

std::string transactions::getDate() const
{
    return date;
}

void transactions::setDate(const std::string &value)
{
    date = value;
}

std::string transactions::getOthercard() const
{
    return othercard;
}

void transactions::setOthercard(const std::string &value)
{
    othercard = value;
}

std::string transactions::getOthername() const
{
    return othername;
}

void transactions::setOthername(const std::string &value)
{
    othername = value;
}

std::string transactions::getOwncard() const
{
    return owncard;
}

void transactions::setOwncard(const std::string &value)
{
    owncard = value;
}

std::string transactions::getOwnuser() const
{
    return ownuser;
}

void transactions::setOwnuser(const std::string &value)
{
    ownuser = value;
}
void transactions::translist_fill(std::vector<transactions> &translist,QSqlQuery &insertData)
{

     transactions newAction;
     insertData.prepare("SELECT * FROM transactions");
     if(insertData.exec())
      while(insertData.next())
      {
          newAction.ownuser=insertData.value("username").toString().toStdString();
          newAction.owncard=insertData.value("OwnCardNumber").toString().toStdString();
          newAction.amount=insertData.value("amount").toLongLong();
          newAction.othercard=insertData.value("OtherCardNumber").toString().toStdString();
          newAction.othername=insertData.value("otherName").toString().toStdString();
          newAction.date=insertData.value("date").toString().toStdString();
          translist.push_back(newAction);
      }
}

std::string transactions::get_last_date(std::vector<transactions> &translist,std::string ownin)
{   int last=-1;
    int j=0;
    std::string timee;
    for(int i=0;i<translist.size();i++)
    {
        if(translist[i].getOwncard()==ownin)
            if(i>last)
              last=i;
    }
    if(last!=-1)
    {
        for(int i=0;i<translist[last].getDate().size();i++)
        {
            if(translist[last].getDate()[i]==' ')break;
            else timee+=translist[last].getDate()[i];
        }
    }
    else timee="-1";
    return timee;
}

bool transactions::check_ability(std::string Ldate,int Cdate[])
{
    int Lyear,Lmonth,Lday;
    std::string Lyear_str,Lmonth_str,Lday_str;
    for(int i=0;i<5;i++)
    {
        if(Ldate[i]=='/')break;
        else Lyear_str+=Ldate[i];
    }
    int index=5;
    for(index=5;index<Ldate.size();index++)
    {
        if(Ldate[index]=='/')break;
        else Lmonth_str+=Ldate[index];
    }
    index++;
    while(index!=Ldate.size())
        Lday_str+=Ldate[index++];
    Lyear=stoi(Lyear_str);
    Lmonth=stoi(Lmonth_str);
    Lday=stoi(Lday_str);
    if((Cdate[0]>Lyear)||((Cdate[0]=Lyear)&&(Cdate[1]>Lmonth))||((Cdate[0]=Lyear)&&(Cdate[1]=Lmonth)&&(Cdate[2]>Lday)))
        return true;
    else return false;
}
