#ifndef CHATRUNNABLE_H
#define CHATRUNNABLE_H

#include <QRunnable>
#include <QTcpSocket>
#include <QDebug>

class chatRunnable : public QRunnable
{
public:
    chatRunnable(int ID);
    int getSocketDes();
    void setSocketDes(int socketSet);

signals:
   // void error(QTcpSocket::SocketError sockerror);

public slots:
    void readyRead();
    void disconnected();

protected:
    void run();

private:
    int socketDes;
    QTcpSocket *socket;
};

#endif // CHATRUNNABLE_H
