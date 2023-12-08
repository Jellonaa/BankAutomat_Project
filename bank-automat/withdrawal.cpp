#include "withdrawal.h"
#include "ui_withdrawal.h"

Withdrawal::Withdrawal(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Withdrawal)
{
    ui->setupUi(this);
}

Withdrawal::~Withdrawal()
{
    delete ui;
}

void Withdrawal::showBalance(QString rahat)
{
    ui->textRahat->setText(rahat);
}

void Withdrawal::on_btnSulje_clicked()
{
    close();
}

