#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setStyleSheet("Dialog {border-image: url(:/new/prefix1/login2.jpg);}");
    ui->GName->setPlaceholderText("Name");
    ui->Gfamily->setPlaceholderText("Surname");
    ui->GUser->setPlaceholderText("Username");
    ui->Gpass->setPlaceholderText("Password");
    ui->GID->setPlaceholderText("SS Number");
    ui->GAge->setPlaceholderText("Age(years)");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_BRegister_clicked()
{

}
