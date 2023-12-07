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

    void setFname(const QString &newFname);

    void setLname(const QString &newLname);

private slots:
    void getNameSlot (QNetworkReply *reply);

private:
    Ui::BankMenu *ui;
    QString fname,lname;
    void showName();
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // BANKMENU_H
