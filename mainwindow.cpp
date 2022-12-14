#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <typeinfo>

//MAIN (SUM vs XOR) PROBLEM
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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    read_config();
}


MainWindow::~MainWindow()
{
    delete ui;
}


//CONFIG READER
void MainWindow::read_config()
{
    //FINDING THE TEXT FILE
    QFile file("./urls.txt");
    if(!file.exists()){
        qDebug() << "File Not Found";
    }else if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "CANNOT OPEN";
    }else{
        //CREATING A STREAM FOR READING TXT FILE
        QTextStream stream(&file);
        //READ ONE LINE
        QString data = stream.readLine();
        //SPLITTING DATA
        QStringList list =data.split('=');
        //ASSING VALUE
        http_url=list[1];
        while (!stream.atEnd()){
            QString line = stream.readLine();
            qDebug() <<line;
            QStringList list2 =line.split('=');
            tcp_port=list2[1];
            tcp_port.toInt();
        }
    }
}


//HTTP CONNECTION REQUEST
void MainWindow::on_httpButton_clicked()
{
    qDebug()<<"Requested";
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    connect(man, &QNetworkAccessManager::finished, this, &MainWindow::requestFinished);
    QUrl url = QUrl(http_url);
    man->get(QNetworkRequest(url));
}
//HTTP RESPONSE HANDLE
void MainWindow::requestFinished(QNetworkReply *reply) {
    QByteArray bts = reply->readAll();
    //Type Casting Start
    QString str(bts);
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject obj = doc.object();
    //Type Casting End
    ui->httpLabel->setText(SumXor(obj.value("data").toInt()));
}


// TCP CONNECTION
void MainWindow::on_tcpButton_clicked()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("localhost",tcp_port.toInt());
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
    ui->tcpLabel->setText(SumXor(i));
    socket->close();
}


