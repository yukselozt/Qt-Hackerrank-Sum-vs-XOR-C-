#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QNetworkAccessManager> //to make request
#include <QNetworkReply> //to handle reply
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include<QTcpSocket>
#include<QFile>
#include <config.h>
#include<QSettings>
#include<QtWebSockets/QWebSocket>
#include <QtCore/QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void configReader();
    void ws_connection();
    void onTextMessageReceived(const QString &message);
    void onConnected();

Q_SIGNALS:
    void closed();


private slots:
    void on_httpButton_clicked();
    void requestFinished(QNetworkReply*);
    void on_tcpButton_clicked();


private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QWebSocket *webSocket;

};
#endif // MAINWINDOW_H
