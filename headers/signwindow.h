#ifndef SIGNWINDOW_H
#define SIGNWINDOW_H
#include "mainwindow.h"
#include <QMainWindow>
#include"users.h"
#include "transactions.h"

namespace Ui {
class signWindow;
}

class signWindow : public QMainWindow
{
    Q_OBJECT
    MainWindow*Loginpage;
    vector<users> account;
    vector<cards> bank;
     QSqlDatabase database;
    QSqlQuery insertData;
    vector<transactions>translist;

public:
    explicit signWindow( QSqlDatabase &,QSqlQuery&,MainWindow*,vector<transactions>&,vector<cards>&,vector<users>&,QWidget *parent = nullptr);
    ~signWindow();

private slots:
    void on_Bmakeacc_clicked();

    void on_BLogin_clicked();

    void on_BaddPhoto_clicked();

    void on_Bvisiable_clicked();

private:
    Ui::signWindow *ui;
};

#endif // SIGNWINDOW_H
