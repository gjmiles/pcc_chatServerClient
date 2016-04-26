#ifndef CHATTHREADS_H
#define CHATTHREADS_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>
#include <QTimer>
#include <QMap>

class chatThreads : public QThread
{
    Q_OBJECT
public:
    explicit chatThreads(int ID, QObject *parent = 0);
    void run();
    QHostAddress threadIP();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void outgoingMessage(QString name, QByteArray out);
    void outIP(QString name, QHostAddress ipOut);
    //void userName(QString name);
    
public slots:
    void readyRead();
    void disconnected();
    void incomingMessage(QString name, QByteArray otherChat);
    void warnings(QString name, QString level, QHostAddress probIP);
    void blockIP(QMap<QString,QHostAddress> blockedIP);

private:
    QTcpSocket *socket;
    int socketDes;
    QByteArray serverData;
    QString chatName;
    QHostAddress gotIP;
};

#endif // CHATTHREADS_H
