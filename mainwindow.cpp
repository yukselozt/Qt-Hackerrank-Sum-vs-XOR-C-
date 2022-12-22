#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <typeinfo>
#include<QSettings>

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
    configReader();
    ws_connection();
}


MainWindow::~MainWindow()
{
    delete ui;
}


////WEBSOCKET CONNECTION
//void MainWindow::getMessage(const QString &message){
//    qDebug()<<message;
//    ui->wsLabel->setText(message);
//}


//CONFIG READER
void MainWindow::configReader(){
    QString qstrConfigPath = QApplication::applicationDirPath();
    qstrConfigPath.append("/Config/config.ini");
    QSettings settings(qstrConfigPath,QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    settings.beginGroup("HTTP_VALUES");
    QList<QString> keys_list;
    //qDebug()<<keys_list;
    config::HTTP_URL = settings.value("http_url").toString();
    settings.endGroup();

    settings.beginGroup("TCP_VALUES");
    config::TCP_HOST= settings.value("host").toString();
    config::TCP_PORT= settings.value("port").toInt();
    settings.endGroup();

}


//HTTP CONNECTION REQUEST
void MainWindow::on_httpButton_clicked()
{
    qDebug()<<"Requested";
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    connect(man, &QNetworkAccessManager::finished, this, &MainWindow::requestFinished);
    QUrl url = QUrl(config::HTTP_URL);
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
    socket->connectToHost(config::TCP_HOST,config::TCP_PORT);
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
    }else{
        qDebug() << "Not Connected!!";
    }
    socket->write("hello");
    socket->waitForBytesWritten(1000);
    socket->waitForReadyRead(3000);
    char c =socket->readAll().at(0);
    int i = c - '0';
    ui->tcpLabel->setText(SumXor(i));
    socket->close();
}


//WS CONNECTION
void MainWindow::ws_connection()
{
    webSocket = new QWebSocket();
    connect(webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(webSocket, &QWebSocket::disconnected, this, &MainWindow::closed);
    webSocket -> open(QUrl("ws://localhost:1880/ws/publish"));
}

void MainWindow::onConnected()
{

        qDebug() << "WebSocket connected";
    connect(webSocket, &QWebSocket::textMessageReceived,
            this, &MainWindow::onTextMessageReceived);
    webSocket->sendTextMessage(QStringLiteral("Hello, world!"));
}

void MainWindow::onTextMessageReceived(const QString &message)
{

        qDebug() << "Message received:" << message;
    webSocket->close();
}





