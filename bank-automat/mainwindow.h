
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bankmenu.h"
#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void authenticateUser();


    void loginButton_clicked();
    void getNameSlot (QNetworkReply *reply);
    void setName (QNetworkReply *reply);
    void handleBtnNumber();
    void handleBtnClear();

private:
    Ui::MainWindow *ui;
    BankMenu *objectBankMenu;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
    bool editPass = false;
};

#endif // MAINWINDOW_H
