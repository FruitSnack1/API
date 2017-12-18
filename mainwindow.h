#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int dwn;

    QPixmap getImg() const;
    void setImg(const QPixmap &value);

private slots:
    void on_pushButton_clicked();

    void downloadFinished(QNetworkReply *reply);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
    QNetworkAccessManager manager2;
    QPixmap img;
};

#endif // MAINWINDOW_H
