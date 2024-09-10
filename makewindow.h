#ifndef MAKEWINDOW_H
#define MAKEWINDOW_H
#include <QMainWindow>
#include "transactions.h"
#include "users.h"
#include "panelwindow.h"
namespace Ui {
class MakeWindow;
}

class MakeWindow : public QMainWindow
{
    Q_OBJECT
    vector<cards> bank;
    panelWindow* panelPage;
     QSqlDatabase database;
    vector<users> account;
    QSqlQuery insertData;
    vector<transactions>translist;

public:
    explicit MakeWindow( QSqlDatabase &,QSqlQuery &,panelWindow*,vector<transactions>&,vector<cards>&,vector<users>&,QWidget *parent = nullptr);
    ~MakeWindow();

private slots:
    void on_Bback_clicked();

    void on_Bmakeacc_clicked();

    void on_BvisiableOUP_clicked();

    void on_BvisiableDef_clicked();

private:
    Ui::MakeWindow *ui;
};

#endif // MAKEWINDOW_H
