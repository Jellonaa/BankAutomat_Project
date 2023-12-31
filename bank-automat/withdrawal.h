#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class Withdrawal;
}

class Withdrawal : public QDialog
{
    Q_OBJECT

public:
    explicit Withdrawal(QWidget *parent = nullptr);
    ~Withdrawal();
    void showBalance(QString);
    void showCredit(QString);
    void setId(const QString &newId);
    QString id;
    void setCredit(const QString &newCredit);
    QString credit;
    void setOwner(const QString &newOwner);
    QString owner;

private slots:
    void on_btnSulje_clicked();
    void handleBtnNumber();
    void handleBtnClear();
    void on_btnHyvaksy_clicked();

    void updateBalanceSlot (QNetworkReply *reply);
    void getBalanceSlot(QNetworkReply *reply);

private:
    Ui::Withdrawal *ui;
    QNetworkAccessManager *putManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QNetworkAccessManager *getManager;
};

#endif // WITHDRAWAL_H
