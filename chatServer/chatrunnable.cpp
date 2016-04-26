#include "chatrunnable.h"

chatRunnable::chatRunnable(int ID)
{
    this->socketDes = ID;
}

int chatRunnable::getSocketDes()
{
    return socketDes;
}

void chatRunnable::setSocketDes(int socketSet)
{
    socketDes = socketSet;
}

void chatRunnable::run()
{
    //if(!socketDes) return;
    qDebug() << "Starting thread";

    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(socketDes))
    {
        //emit error(socket->error());
        return;
    }

     qDebug() << socketDes << " Client Connected";

   //connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
   //connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

     QByteArray data = socket->readAll();
    qDebug() << socketDes << " Data in: " << data;

    socket->write(data);


   // socket.write("BLEGH");
   // socket.flush();
   // socket.waitForBytesWritten();
//    socket.close();

}

void chatRunnable::readyRead()
{
    QByteArray data = socket->readAll();
    qDebug() << socketDes << " Data in: " << data;

    socket->write(data);

}

void chatRunnable::disconnected()
{
    socket->deleteLater();
    exit(0);
}
