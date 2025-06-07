#ifndef BALANCEWINDOW_H
#define BALANCEWINDOW_H
#include "users.h"
#include <QMainWindow>
#include "transactions.h"
#include "panelwindow.h"
namespace Ui {
class balanceWindow;
}

class balanceWindow : public QMainWindow
{
    Q_OBJECT
    vector<cards> bank;
    vector<users> account;
    panelWindow* panelPage;
    vector<transactions>translist;

public:
    explicit balanceWindow(panelWindow*,vector<transactions>&,vector<cards>&,vector<users>&,QWidget *parent = nullptr);
    ~balanceWindow();
    void update_info(vector<cards>&bank,vector<users>&account);

private slots:
    void on_Bback_clicked();

    void on_Bbalance_clicked();

    void on_Bverify_clicked();

private:
    Ui::balanceWindow *ui;
};

#endif // BALANCEWINDOW_H
