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
#include<QWebSocket>
#include<QWebSocketServer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class WebServer;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void configReader();


private slots:
    void on_httpButton_clicked();
    void requestFinished(QNetworkReply*);
    void on_tcpButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
};
#endif // MAINWINDOW_H
