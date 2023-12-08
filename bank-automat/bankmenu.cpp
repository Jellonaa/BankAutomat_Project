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

void BankMenu::setId(const QString &newId)
{
    id = newId;
}


void BankMenu::on_btnKirjauduUlos_clicked()
{
    close();
}


void BankMenu::on_btnNostaRahaa_clicked()
{
    objectWithdrawal = new Withdrawal(this);

    QString site_url="http://localhost:3000/card/" + id;
    QNetworkRequest request((site_url));
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getAccountSlot(QNetworkReply*)));

    reply = getManager->get(request);


}

void BankMenu::getAccountSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString account;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        account+=(json_obj["card_account"].toString());
    }

    reply->deleteLater();
    getManager->deleteLater();

    QString site_url="http://localhost:3000/account/" + account;
    QNetworkRequest request((site_url));
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getBalanceSlot(QNetworkReply*)));

    reply = getManager->get(request);
}

void BankMenu::getBalanceSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString balance = json_obj["balance"].toString();
    qDebug()<<balance;
    objectWithdrawal->showBalance(balance+" €");

    reply->deleteLater();
    getManager->deleteLater();

    objectWithdrawal->show();
}
