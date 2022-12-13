#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <typeinfo>


QString SumXor (int x){
    int counter = 0;
    for(int i = 0; i <= x; i++){
        if((x^i) ==(x+i)){
            counter++;
        }
    }
    QString ret = QString::number(counter);
    return ret;
}


void MainWindow::requestFinished(QNetworkReply *reply) {
    QByteArray bts = reply->readAll();
    //Type Casting Start
    QString str(bts);
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject obj = doc.object();
    //Type Casting End
    ui->httpLabel->setText(SumXor(obj.value("data").toInt()));

}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_httpButton_clicked()
{
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    connect(man, &QNetworkAccessManager::finished, this, &MainWindow::requestFinished);
    QUrl url = QUrl(http_url);
    man->get(QNetworkRequest(url));
}


void MainWindow::on_tcpButton_clicked()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("localhost",88);
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
    }else{
        qDebug() << "Not Connected!!";
    }
    socket->write("hel");
    socket->waitForBytesWritten(1000);
    socket->waitForReadyRead(3000);
    char c =socket->readAll().at(0);
    int i = c - '0';
    qDebug()<<SumXor(i);
    ui->tcpLabel->setText(SumXor(i));
}

