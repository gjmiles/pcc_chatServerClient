#include "chatthreads.h"

chatThreads::chatThreads(int ID, QObject *parent) :
    QThread(parent)
{
    this->socketDes = ID;
}

void chatThreads::run()
{

    qDebug() << socketDes << " Starting thread";
    socket = new QTcpSocket();

    if(!socket->setSocketDescriptor(this->socketDes))
    {
        emit error(socket->error());
        return;
    }
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

    qDebug() << socketDes << " Chat Client Connected";
    exec();
}

QHostAddress chatThreads::threadIP()
{
   gotIP = socket->peerAddress();
   qDebug() << " Is this the ip address? "<< gotIP;
   return gotIP;
}

void chatThreads::incomingMessage(QString name, QByteArray otherChat)
{
    if(name != chatName)
        socket->write(otherChat);
}

void chatThreads::warnings(QString name, QString level, QHostAddress probIP)
{
    QHostAddress myIP = socket->peerAddress();
    if(name == chatName && myIP == probIP)
        if(level.toUpper() == "YELLOW")
        {
            QByteArray warn("WARNING!!! YOU ARE NOT OBEYING CHAT RULES!!!\nIF YOU CONTINUE YOU WILL BE KICKED!!!");
            socket->write(warn);
        }else if(level.toUpper() == "RED3")
        {
            QByteArray warn("YOU HAVE BEEN PERMA KICKED!!!");
            socket->write(warn);
            QTimer::singleShot(1000,this,SLOT(deleteLater()));
        }else if(level.toUpper() == "RED1")
        {
            QByteArray warn("YOU HAVE BEEN KICKED FOR 10 MINUTES!!!");
            socket->write(warn);
            QTimer::singleShot(1000,this,SLOT(deleteLater()));
        }else if(level.toUpper() == "RED2")
        {
            QByteArray warn("YOU HAVE BEEN KICKED FOR 1 DAY!!!");
            socket->write(warn);
            QTimer::singleShot(1000,this,SLOT(deleteLater()));
        }
}

void chatThreads::blockIP(QMap<QString,QHostAddress> blockedIP)
{

    foreach(QString str, blockedIP.keys())
    {

        if(gotIP == blockedIP[str])
        {

            socket->abort();
            return;
        }
    }

}

void chatThreads::readyRead()
{
    serverData = socket->readAll();
    //gotIP = socket->peerAddress();
    if(chatName.isEmpty())
    {
        gotIP = socket->peerAddress();
        chatName = serverData;

        emit outIP(chatName, gotIP);
        return;
       // emit userName(chatName);
    }


     do
     {
         emit outgoingMessage(chatName, serverData);
     }while(socket->bytesAvailable());

     socket->write(serverData);
}

void chatThreads::disconnected()
{

    socket->deleteLater();
    exit(0);
}
