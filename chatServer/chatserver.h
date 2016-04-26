#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QThreadPool>
#include <QDebug>
#include <QHostAddress>
#include <QMap>
#include <QDateTime>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QVector>
//#include "chatrunnable.h"
#include "chatthreads.h"


class chatserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit chatserver(QObject *parent = 0);
    void serverStart();
    void leftChat(QString name);
    QString qstringDatRet();
    void sendToChat(QString sending);
    void newPar(QString name);
    bool checkForCommand(QString command, QString name);
    void clientCommands(QString command, QString name);
    void logChat(QString chats, QString currentDate);

protected:
    //void incomingConnection(int handle);
    void incomingConnection(int socketDes);
signals:
    void outgoingMessage();
    void toThread(QString name, QByteArray out);
    void warnThread(QString name, QString level, QHostAddress probIP);
    void sendIP(QMap<QString,QHostAddress> outMap);

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void dataToChat(QString name, QByteArray in);
    void grabIP(QString name, QHostAddress ipIn);
    void serverCommands(QString name, QString command);
    //void blockIP(int socketDes);

private slots:
    void unBlock();


private:
   // QThreadPool *chatpool;
    QTcpSocket *mainSocket;
    QTcpServer *blockServer;
    QByteArray data;
    QMap<QString,QHostAddress> clientIP;
    QMap<QString,QHostAddress> blockedIP;
    QVector<QString> unblockList;
};

#endif // CHATSERVER_H
