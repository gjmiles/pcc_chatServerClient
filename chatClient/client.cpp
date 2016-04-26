#include "client.h"

client::client(QObject *parent) :
    QObject(parent)
{
    /*
    socket = new QTcpSocket(this);

    //connect(socket,SIGNAL(connected()),this,SLOT(connected()));

    socket->connectToHost("127.0.0.1",8085);

    if(!socket->waitForConnected(3000))
    {
        qDebug()  << "Error: " << socket->errorString();
    }
    else
    {
        connect(socket,SIGNAL(connected()),this,SLOT(connected()));
        connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    }
    */

}

client::~client()
{
    //goodBye();
    //QTimer::singleShot(1000,this,SLOT());
    //qDebug() << "Client destroyed";
   // socket->deleteLater();
     //exit(0);
}

bool client::clientStart()
{
    socket = new QTcpSocket(this);

    //connect(socket,SIGNAL(connected()),this,SLOT(connected()));

    socket->connectToHost("<IP ADDRESS>",8085); // Hard coded IP needs to be configurable

    if(!socket->waitForConnected(3000))
    {
        qDebug()  << "Error: " << socket->errorString();
        return false;
    }
    else
    {
        connect(socket,SIGNAL(connected()),this,SLOT(connected()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
        connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
        return true;
    }
}

void client::connected()
{
    qDebug() << "Connected!";
}

void client::reConnect()
{
     socket->connectToHost("127.0.0.1",8085);
      if(!socket->waitForConnected(3000))
        qDebug()  << "Error: " << socket->errorString();
}

void client::disconnected()
{
    qDebug() << "Disconnected";
    socket->disconnectFromHost();

}      

void client::sendToServer(QString sending)
{
    if(sending.isEmpty())
        return;
    QByteArray temp = sending.toUtf8();
    socket->write(temp);
}

bool client::commands(QString command)
{
    if(command.at(1).toUpper() == 'B')
    {
        goodBye();
        return true;
    }
    else
        return false;
}

QString client::qstringDatRet()
{
    QString temp(data);
    return temp;
}

void client::readyRead()
{
    data = socket->readAll();

    qDebug() << " Data in: " << data;

    do
    {
        emit incomingMessage();
    }while(socket->bytesAvailable());

    //socket->write(data);
}

void client::getName(QString name)
{
    chatName = name;
}

void client::goodBye()
{
    QByteArray bye;
    QString temp = "%Bye " + chatName;
    bye = temp.toUtf8();
    socket->write(bye);
    socket->disconnectFromHost();
}



void client::bytesWritten(qint64 bytes)
{
}


