#ifndef USERS_H
#define USERS_H
#include <QString>
#include "cards.h"
#include <QPixmap>
#include <vector>
#include <QtSql>
#include <QSqlDatabase>
#include "linklist.h"

class users
{
private:
        std::string name;
        std::string family;
        std::string age;
        std::string id;
        std::string username;
        std::string pass;
        std::string pic;
        link_list<cards> ll;
public:
        users();
        static void fill(vector<users> &account,QSqlQuery &insertData);
        std::string getName() const;
        void setName(const std::string &value);
        std::string getFamily() const;
        void setFamily(const std::string &value);
        std::string getAge() const;
        void setAge(const std::string &value);
        std::string getId() const;
        void setId(const std::string &value);
        std::string getUsername() const;
        void setUsername(const std::string &value);
        std::string getPass() const;
        void setPass(const std::string &value);
        std::string getPic() const;
        void setPic(const std::string &value);
        link_list<cards>& getLl();
        void setLl(const link_list<cards> &value);
};
#endif
