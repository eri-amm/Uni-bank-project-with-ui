#ifndef TRANSWINDOW_H
#define TRANSWINDOW_H
#include "users.h"
#include "panelwindow.h"
#include <QMainWindow>
#include "transactions.h"

namespace Ui {
class transWindow;
}

class transWindow : public QMainWindow
{
    Q_OBJECT
    vector<cards> bank;
    QSqlQuery insertData;
    panelWindow* panelPage;
     QSqlDatabase database;
    vector<users> account;
    vector<transactions>translist;

public:
    explicit transWindow(  QSqlDatabase&,QSqlQuery &,panelWindow*,vector<transactions>&,vector<cards>&,vector<users>&,QWidget *parent = nullptr);
    ~transWindow();
    void update_info(vector<cards>&bank,vector<users>&account);

private slots:
    void on_Bback_clicked();

    void on_Bmessage_clicked();

    void on_Btransfer_clicked();

    void on_BvisiableDy_clicked();

    void on_BvisiableStat_clicked();

    void on_Bverify_clicked();

private:
    Ui::transWindow *ui;
};

#endif // TRANSWINDOW_H
