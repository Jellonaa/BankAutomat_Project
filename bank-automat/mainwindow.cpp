#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::authenticateUser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::authenticateUser()
{

    QString username = ui->username->text();
    QString password = ui->password->text();



    QJsonObject userObject;
    userObject["username"] = username;
    userObject["password"] = password;

    QJsonDocument userDocument(userObject);
    QByteArray userData = userDocument.toJson();


    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("http://localhost:3000/login")); // Korvaa oikealla URL:llä
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, userData);



    connect(reply, &QNetworkReply::finished, [=]() {
        //if (reply->error() == QNetworkReply::NoError) {
        if(reply->readAll() !="false"){

            qDebug() << "Kirjautuminen onnistui!";
            objectBankMenu = new BankMenu(this);
            objectBankMenu->show();
            ui->labelInfo->setText("");

        } else {

            qDebug() << "Virhe kirjautumisessa:" << reply->errorString();
            //qDebug() << "Virhe kirjautumisessa:" << reply->readAll();
            ui->labelInfo->setText("Virhe kirjautumisessa");
        }

        reply->deleteLater();
        manager->deleteLater();
    });
}
