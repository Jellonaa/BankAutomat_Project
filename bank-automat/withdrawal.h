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

private slots:
    void on_btnSulje_clicked();

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
