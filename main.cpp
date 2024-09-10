#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"
#include <QApplication>
#include <vector>
#include "timess.h"
#include "linklist.h"
#include "transactions.h"
int main(int argc, char *argv[])
{
    QSqlDatabase database= QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("C:/Users/ASUS/Documents/untitled15/uiap-sec-mini-project-eri-amm/mydb");
    database.open();
    QSqlDatabase::database().transaction();
    QSqlQuery insertData(database);
    QSqlQuery selectData(database);
    vector<users> account;
    vector<cards> bank;
    vector<transactions> translist;
    users::fill(account,selectData);
    cards::cards_fill(bank,selectData);
    transactions::translist_fill(translist,selectData);
    QApplication a(argc, argv);
    MainWindow w(database,insertData,translist,bank,account);
    w.show();
    return a.exec();
}


