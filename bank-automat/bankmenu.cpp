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

void BankMenu::setFname(const QString &newFname)
{
    fname = newFname;
}

void BankMenu::setLname(const QString &newLname)
{
    lname = newLname;
}

void BankMenu::showName()
{

    ui->textNimi->setText(fname+" "+lname);
}

void BankMenu::getNameSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString name;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        name+=(json_obj["fname"].toString())+" "+json_obj["lname"].toString();
    }

    ui->textNimi->setText(name);

    reply->deleteLater();
    getManager->deleteLater();
}
