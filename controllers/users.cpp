#include "users.h"
#include <fstream>
#include "linklist.h"
#include <vector>
#include <QString>
#include <QtSql>
#include <QMessageBox>
#include <QSqlDatabase>
using namespace std;

users::users()
{
    pic=":/new/prefix1/user.png";
}

link_list<cards>& users::getLl()
{
    return ll;
}

void users::setLl(const link_list<cards> &value)
{
    ll = value;
}

std::string users::getPic() const
{
    return pic;
}

void users::setPic(const std::string &value)
{
    pic = value;
}

std::string users::getPass() const
{
    return pass;
}

void users::setPass(const std::string &value)
{
    pass = value;
}

std::string users::getUsername() const
{
    return username;
}

void users::setUsername(const std::string &value)
{
    username = value;
}

std::string users::getId() const
{
    return id;
}

void users::setId(const std::string &value)
{
    id = value;
}

std::string users::getAge() const
{
    return age;
}

void users::setAge(const std::string &value)
{
    age = value;
}

std::string users::getFamily() const
{
    return family;
}

void users::setFamily(const std::string &value)
{
    family = value;
}

std::string users::getName() const
{
    return name;
}

void users::setName(const std::string &value)
{
    name = value;
}
void users::fill(vector<users> &account,QSqlQuery &insertData)
{

    users newUser;
    insertData.prepare("SELECT * FROM users");
    if(insertData.exec())
     while(insertData.next())
     {
         newUser.username=insertData.value("username").toString().toStdString();
         newUser.pass=insertData.value("password").toString().toStdString();
         newUser.name=insertData.value("firstname").toString().toStdString();
         newUser.family=insertData.value("lastname").toString().toStdString();
         newUser.id=insertData.value("IdNum").toString().toStdString();
         newUser.age=insertData.value("age").toString().toStdString();
         newUser.pic=insertData.value("picAddress").toString().toStdString();
         account.push_back(newUser);
     }
}
