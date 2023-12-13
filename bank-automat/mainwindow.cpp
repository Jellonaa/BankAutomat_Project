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

    connect(ui->btn0, SIGNAL(clicked()), this, SLOT(handleBtnNumber()));
    connect(ui->btn1, SIGNAL(clicked()), this, SLOT(handleBtnNumber()));
    connect(ui->btn2, SIGNAL(clicked()), this, SLOT(handleBtnNumber()));
    connect(ui->btn3, SIGNAL(clicked()), this, SLOT(handleBtnNumber()));
    connect(ui->btn4, SIGNAL(clicked()), this, SLOT(handleBtnNumber()));
    connect(ui->btn5, SIGNAL(clicked()), this, SLOT(handleBtnNumber()));
    connect(ui->btn6, SIGNAL(clicked()), this, SLOT(handleBtnNumber()));
    connect(ui->btn7, SIGNAL(clicked()), this, SLOT(handleBtnNumber()));
    connect(ui->btn8, SIGNAL(clicked()), this, SLOT(handleBtnNumber()));
    connect(ui->btn9, SIGNAL(clicked()), this, SLOT(handleBtnNumber()));
    connect(ui->btnClear, SIGNAL(clicked()), this, SLOT(handleBtnClear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::authenticateUser()
{
    if (ui->password->text() != "") {

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
            ui->labelInfo->setText("");

            objectBankMenu = new BankMenu(this);
            objectBankMenu->setId(ui->username->text());
            loginButton_clicked();
            objectBankMenu->show();
        } else {

            qDebug() << "Virhe kirjautumisessa:" << reply->errorString();
            //qDebug() << "Virhe kirjautumisessa:" << reply->readAll();
            ui->labelInfo->setText("Virhe kirjautumisessa");
        }

        reply->deleteLater();
        manager->deleteLater();

        });
    } else {
        editPass = true;
    }
}

void MainWindow::loginButton_clicked()
{
    QString site_url="http://localhost:3000/card/" + ui->username->text();
    QNetworkRequest request((site_url));
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getNameSlot(QNetworkReply*)));

    reply = getManager->get(request);
}


void MainWindow::getNameSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString owner_id;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        owner_id+=QString::number(json_obj["card_owner"].toInt());
    }

    QString site_url="http://localhost:3000/customer/" + owner_id;
    QNetworkRequest request((site_url));
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(setName(QNetworkReply*)));

    reply = getManager->get(request);
}

void MainWindow::setName(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString name;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        name+=(json_obj["fname"].toString())+" "+json_obj["lname"].toString();
    }


    objectBankMenu->showName(name);

    reply->deleteLater();
    getManager->deleteLater();
}

void MainWindow::handleBtnNumber()
{
    if (editPass == false) {
        QString teksti = ui->username->text();
        QPushButton * button = qobject_cast<QPushButton*>(sender());
        QString numero = button->text();
        ui->username->setText(teksti+numero);
    } if (editPass == true) {
        QString teksti = ui->password->text();
        QPushButton * button = qobject_cast<QPushButton*>(sender());
        QString numero = button->text();
        ui->password->setText(teksti+numero);
    }
}

void MainWindow::handleBtnClear()
{
    ui->password->clear();
    ui->username->clear();
    editPass = false;
}
