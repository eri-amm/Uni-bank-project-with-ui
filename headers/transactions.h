#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include <iostream>
#include <QtSql>
#include <qsqldatabase.h>
#include <ctime>
#include <vector>
class transactions
{
private :

    std::string ownuser;
    std::string owncard;
    std::string othername;
    std::string othercard;
    std::string date;
    long long amount;
public:
    transactions();
    static void translist_fill(std::vector<transactions> &translist,QSqlQuery &insertData);
    static std::string get_last_date(std::vector<transactions> &translist,std::string ownin);
    static bool check_ability(std::string Ldate,int Cdate[3]);
    std::string getOwnuser() const;
    void setOwnuser(const std::string &value);
    std::string getOwncard() const;
    void setOwncard(const std::string &value);
    std::string getOthername() const;
    void setOthername(const std::string &value);
    std::string getOthercard() const;
    void setOthercard(const std::string &value);
    std::string getDate() const;
    void setDate(const std::string &value);
    long long getAmount() const;
    void setAmount(const long long &value);
};

#endif // TRANSACTIONS_H
