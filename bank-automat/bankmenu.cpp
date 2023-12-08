#include "bankmenu.h"
#include "ui_bankmenu.h"

BankMenu::BankMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BankMenu)
{
    ui->setupUi(this);
}

BankMenu::~BankMenu()
{
    delete ui;
}

void BankMenu::showName(QString name)
{

    ui->textNimi->setText(name+"!");
}

