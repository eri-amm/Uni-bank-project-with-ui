#ifndef PASSWINDOW_H
#define PASSWINDOW_H
#include"users.h"
#include "transactions.h"
#include <QMainWindow>
#include "panelwindow.h"
namespace Ui {
class passWindow;
}

class passWindow : public QMainWindow
{
    Q_OBJECT
    vector<cards> bank;
    panelWindow* panelPage;
    QSqlQuery insertData;
     QSqlDatabase database;
    vector<users> account;
    vector<transactions>translist;
public:
    explicit passWindow( QSqlDatabase &,QSqlQuery &,panelWindow*,vector<transactions>&,vector<cards>&,vector<users>&,QWidget *parent = nullptr);
    ~passWindow();
    void update_info(vector<cards>&bank,vector<users>&account);

private slots:
    void on_Bback_clicked();

    void on_BChange_clicked();

    void on_BvisiablePre_clicked();

    void on_BvisiableNew_clicked();

    void on_BvisiableCon_clicked();

    void on_Bverify_clicked();

private:
    Ui::passWindow *ui;
};

#endif // PASSWINDOW_H
