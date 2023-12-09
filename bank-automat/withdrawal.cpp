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

void Withdrawal::showCredit(QString credit)
{
    if (credit.toFloat() > 0) {
        ui->textLuottoLuku->setText(credit);
        ui->textLuottoEuro->setText("€");
        ui->textLuotto->setText("Luotto :");
    } else {
        ui->textLuottoLuku->setText("");
        ui->textLuottoEuro->setText("");
        ui->textLuotto->setText("");
    }
}

void Withdrawal::setId(const QString &newId)
{
    id = newId;
}

void Withdrawal::setCredit(const QString &newCredit)
{
    credit = newCredit;
}

void Withdrawal::setOwner(const QString &newOwner)
{
    owner = newOwner;
}

void Withdrawal::on_btnSulje_clicked()
{
    close();
}


void Withdrawal::on_btnHyvaksy_clicked()
{
    float rahat = ui->textRahat->text().toFloat();
    float nosto = floorf(ui->lineEdit->text().toFloat()*100)/100;
    float luotto = ui->textLuottoLuku->text().toFloat();

    //qDebug() << rahat;
    //qDebug() << nosto;

    if (nosto > 0) {
        if (rahat + luotto - nosto >= 0) {
            QJsonObject jsonObj;
            jsonObj.insert("balance", rahat - nosto);
            jsonObj.insert("credit", credit);
            jsonObj.insert("owner", owner);
            // Olisin tehnyt tämän patch-requestilla mutta en osannut tehdä sallaista QT:lla

            QString site_url="http://localhost:3000/account/" + id;
            QNetworkRequest request((site_url));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

            putManager = new QNetworkAccessManager(this);
            connect(putManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(updateBalanceSlot(QNetworkReply*)));

            reply = putManager->put(request, QJsonDocument(jsonObj).toJson());
            ui->textInfo->setText("Nostettiin "+ QString::number(nosto) +" €");
        } else {
            ui->textInfo->setText("Tilillä ei ole tarpeeksi rahaa tähän");
        }
    } else {
        ui->textInfo->setText("Anna nollaa suurempi luku");
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
    //qDebug()<<balance;
    showBalance(balance);

    reply->deleteLater();
    getManager->deleteLater();
}
