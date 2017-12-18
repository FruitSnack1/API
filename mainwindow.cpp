#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QByteArray>
#include <QTime>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&manager,
            SIGNAL(finished(QNetworkReply*)),
            SLOT(downloadFinished(QNetworkReply*)));
    connect(&manager2,
            SIGNAL(finished(QNetworkReply*)),
            SLOT(downloadFinished(QNetworkReply*)));
    dwn = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text().length() > 0){
        QNetworkRequest request;
        QString tag = ui->lineEdit->text();
        qint64 time = QDateTime::currentMSecsSinceEpoch()/1000 - qrand() % 86400000;
        qDebug() << time;
        QUrl url("https://api.tumblr.com/v2/tagged?tag=" + tag + "&api_key=EnC07YXUVAaCtbqNXqtkwNujf2BLluhFfrwE8Gbyotx8zBAy7o&limit=1&before=" + QString::number(time));
        qDebug() << "URL: " + url.toString();
        request.setUrl(url);
        manager.get(request);
    }else{
        QMessageBox::information(this, "Info", "No tag");
    }
}

void MainWindow::downloadFinished(QNetworkReply *reply)
{
    if(!reply->url().toString().contains("api")){
        //qDebug() << reply->size();
        //qDebug() << reply->url();
        QByteArray arr = reply->readAll();
        if(arr.size() == 0){
            if(dwn<10){
                on_pushButton_clicked();
                qDebug() << "another one";
                dwn++;
                qDebug() << "NUMBER OF TRY : "+ QString::number(dwn);
            }else{
                QMessageBox::information(this, "Oops", "Nothing found :(");
                dwn = 0;
            }
        }else{

            QImage img = QImage::fromData(arr);
            img = img.scaledToWidth(500);
            QPixmap map;
            map.convertFromImage(img);
            ui->label_2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->label_2->setPixmap(map);
            setImg(map);
            dwn = 0;
        }
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        //qDebug() << reply->readAll();
        QJsonObject doc_obj = doc.object();
        //qDebug() << doc_obj;
        QJsonArray response = doc_obj["response"].toArray();
        QJsonArray photos = response.at(0).toObject()["photos"].toArray();
        QJsonValue url = photos.at(0).toObject()["original_size"].toObject()["url"];
        QNetworkRequest request;
        request.setUrl(QUrl(url.toString()));
        //qDebug() << "IMAGE : " + url.toString();
        manager2.get(request);
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    if(!getImg().isNull()){
        QFile file(QFileDialog::getSaveFileName(this, "Save image","","*.png"));
        file.open(QIODevice::WriteOnly);
        getImg().save(&file, "PNG");
        file.close();
    }else{
        QMessageBox::warning(this, "Warning", "There is no image. WTF do u want to save ?");
    }
}

QPixmap MainWindow::getImg() const
{
    return img;
}

void MainWindow::setImg(const QPixmap &value)
{
    img = value;
}
