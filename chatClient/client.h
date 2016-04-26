#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>

class client : public QObject
{
    Q_OBJECT
public:
    explicit client(QObject *parent = 0);
    ~client();
    bool clientStart();
    void sendToServer(QString sending);
    bool commands(QString command);
    QString qstringDatRet();
    void reConnect();

signals:
    void incomingMessage();

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void getName(QString name);
    void goodBye();

private:
    QTcpSocket *socket;
    QByteArray data;
    QString chatName;
};

#endif // CLIENT_H
