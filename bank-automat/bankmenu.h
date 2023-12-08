#ifndef BANKMENU_H
#define BANKMENU_H

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

private:
    Ui::BankMenu *ui;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // BANKMENU_H
