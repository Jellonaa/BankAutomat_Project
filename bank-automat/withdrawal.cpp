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

void Withdrawal::setId(const QString &newId)
{
    id = newId;
}

void Withdrawal::on_btnSulje_clicked()
{
    close();
}


void Withdrawal::on_btnHyvaksy_clicked()
{
    float rahat = ui->textRahat->text().toFloat();
    float nosto = ui->lineEdit->text().toFloat();

    //qDebug() << rahat;
    //qDebug() << nosto;

    if (nosto > 0) {
        if (rahat - nosto >= 0) {
            QJsonObject jsonObj;
            jsonObj.insert("balance",-(ui->lineEdit->text().toFloat()));

            QString site_url="http://localhost:3000/account/" + id;
            QNetworkRequest request((site_url));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

            putManager = new QNetworkAccessManager(this);
            connect(putManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(updateBalanceSlot(QNetworkReply*)));

            reply = putManager->put(request, QJsonDocument(jsonObj).toJson());
            ui->textInfo->setText("Nostettiin "+ QString::number(nosto) +" €");
        } else {
            ui->textInfo->setText("Ei tarpeeksi rahaa tähän");
        }
    } else {
        ui->textInfo->setText("Anna positiivinen luku");
    }
}

void Withdrawal::updateBalanceSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    putManager->deleteLater();

    QString site_url="http://localhost:3000/account/" + id;
    QNetworkRequest request((site_url));
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getBalanceSlot(QNetworkReply*)));

    reply = getManager->get(request);
}

void Withdrawal::getBalanceSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString balance = json_obj["balance"].toString();
    qDebug()<<balance;
    showBalance(balance);

    reply->deleteLater();
    getManager->deleteLater();
}
