#ifndef BANKMENU_H
#define BANKMENU_H

#include "withdrawal.h"
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class BankMenu;
}

class BankMenu : public QDialog
{
    Q_OBJECT

public:
    explicit BankMenu(QWidget *parent = nullptr);
    ~BankMenu();
    void showName(QString);
    void setId(const QString &newId);
    QString id;

private slots:
    void on_btnKirjauduUlos_clicked();

    void on_btnNostaRahaa_clicked();
    void getAccountSlot(QNetworkReply *reply);
    void getBalanceSlot(QNetworkReply *reply);

private:
    Ui::BankMenu *ui;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
    Withdrawal *objectWithdrawal;
};

#endif // BANKMENU_H
