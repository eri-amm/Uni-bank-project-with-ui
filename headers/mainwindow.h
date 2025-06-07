#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsEffect>
#include <QSql>
#include <QSqlDatabase>
#include "users.h"
#include <QGraphicsBlurEffect>
#include "transactions.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    vector<cards> bank;
    vector<users> account;
    QSqlDatabase database;
    QSqlQuery insertData;
    vector<transactions>translist;
public:
    MainWindow( QSqlDatabase &,QSqlQuery &,vector<transactions>&,vector<cards>&,vector<users>&,QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_BLogin_clicked();

    void on_BRegister_clicked();

    void on_Bvisiable_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
