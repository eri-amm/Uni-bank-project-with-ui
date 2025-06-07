#ifndef PANELWINDOW_H
#define PANELWINDOW_H
#include "users.h"
#include "signwindow.h"
#include "transactions.h"
#include <QMainWindow>

namespace Ui {
class panelWindow;
}

class panelWindow : public QMainWindow
{
    Q_OBJECT
    vector<transactions>translist;
    vector<cards>bank;
     QSqlDatabase database;
    vector<users> account;
    QSqlQuery insertData;

public:
    explicit panelWindow( QSqlDatabase &,QSqlQuery &,vector<transactions>&,vector<cards>&,vector<users>&,QWidget *parent = nullptr);
    ~panelWindow();
    void fill_cards(vector<cards>&bank,vector<users>&account);
    void fill_transactions(vector<transactions>&translist,vector<cards>&bank);

private slots:
    void on_Transaction_clicked();

    void on_Newacc_clicked();

    void on_Balance_clicked();

    void on_Changpass_clicked();

    void on_Exit_clicked();

    void on_setpic_clicked();

    void on_BCpink_clicked();

    void on_BCgreen_clicked();

    void on_BCdefault_clicked();

    void on_get_Display_clicked();

private:
    Ui::panelWindow *ui;
};

#endif // PANELWINDOW_H
