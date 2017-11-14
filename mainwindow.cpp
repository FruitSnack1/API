#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    connect(&manager,
            SIGNAL(finished(QNetworkReply*)),
            SLOT(downloadFinished(QNetworkReply*)));
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.tumblr.com/v2/tagged?tag=lol&api_key=fuiKNFp9vQFvjLNvx4sUwti4Yb5yGutBN4Xh10LXZhhRKjWlV4&limit=1"));
    manager.get(request);
}

void MainWindow::downloadFinished(QNetworkReply *reply)
{
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject doc_obj = doc.object();
    QJsonArray response = doc_obj["response"].toArray();
    QJsonArray photos = response.at(0).toObject()["photos"].toArray();
    QJsonValue url = photos.at(0).toObject()["original_size"].toObject()["url"];

    QByteArray jpg(url.toString().toUtf8());
    QPixmap map;
    map.loadFromData(jpg);
    //ui->label_2->setPixmap(QPixmap::fromImage());
    qDebug() << url.toString();

}
