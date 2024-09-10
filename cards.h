#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <QtSql>
#include <QSqlDatabase>
#include <ctime>
#include <vector>
#include <QString>
using namespace std;

class cards
{
private:
    string username;
    string type;
    string card_number;
    string SHABA;
    string acc_number;
    string cvv2;
    long long balance;
    string limitTime;
    string expire_year;
    string default_pass;
    string default_OUP;
    long translimit;
    string OUP;
public:
    cards();
    static void cards_fill(vector<cards> &bank,QSqlQuery &insertData);
    string getUsername() const;
    void setUsername(const string &value);
    string getType() const;
    void setType(const string &value);
    string getCard_number() const;
    void setCard_number(const string &value);
    string getSHABA() const;
    void setSHABA(const string &value);
    string getAcc_number() const;
    void setAcc_number(const string &value);
    string getCvv2() const;
    void setCvv2(const string &value);
    long long getBalance() const;
    void setBalance(const long long &value);
    string getExpire_year() const;
    void setExpire_year(const string &value);
    string getDefault_pass() const;
    void setDefault_pass(string value);
    string getDefault_OUP() const;
    void setDefault_OUP(string value);
    long getTranslimit() const;
    void setTranslimit(long value);
    string getOUP() const;
    void setOUP(const string &value);
    string getLimitTime() const;
    void setLimitTime(const string &value);
};

#endif // CARDS_H
