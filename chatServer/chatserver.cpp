#include "chatserver.h"

chatserver::chatserver(QObject *parent) :
    QTcpServer(parent)
{

}

void chatserver::serverStart()
{
    if(this->listen(QHostAddress::Any,8085))
    {

        qDebug() << "Chat server up!";
    }
    else
    {
        qDebug() << "Chat server not up!";
    }
}

void chatserver::incomingConnection(int socketDes)
{
    qDebug() << socketDes << " Connecting..";
    QByteArray temp;
    chatThreads *thread = new chatThreads(socketDes,this);
    qRegisterMetaType<QHostAddress>("QHostAddress");
    connect(this, SIGNAL(toThread(QString, QByteArray)),thread,SLOT(incomingMessage(QString,QByteArray)));
    connect(thread, SIGNAL(finished()),thread, SLOT(deleteLater()));
    connect(thread,SIGNAL(outgoingMessage(QString, QByteArray)),this,SLOT(dataToChat(QString, QByteArray)));
    connect(thread,SIGNAL(outIP(QString,QHostAddress)),this,SLOT(grabIP(QString,QHostAddress)));
    connect(this, SIGNAL(warnThread(QString,QString,QHostAddress)),thread,SLOT(warnings(QString,QString,QHostAddress)));

    //connect(thread,SIGNAL(userName(QString)),this,SLOT(grapIP()));
    thread->start();

    if(!blockedIP.isEmpty())
    {
        connect(this,SIGNAL(sendIP(QMap<QString,QHostAddress>)),thread,SLOT(blockIP(QMap<QString,QHostAddress>)));
    }

}

void chatserver::connected()
{
}

void chatserver::disconnected()
{
}

void chatserver::readyRead()
{
    QByteArray data = mainSocket->readAll();

    //qDebug() << " Outgoing "<<data;

    mainSocket->write(data);
}

void chatserver::dataToChat(QString name, QByteArray in)
{
    //qDebug() << " Did you get it ? " << in;
    QString temp(in);
    //qDebug() << " the QByte is now Qstring " << temp;
    if(checkForCommand(temp, name))
        return;
    data = in;
    emit toThread(name, in);
}

void chatserver::grabIP(QString name, QHostAddress ipIn)
{
    //qDebug() << " Did you get the IP? " << ipIn;
    //qDebug() << " How about the name? " << name;
    if(!blockedIP.isEmpty())
    {
        emit sendIP(blockedIP);
        foreach(QString str, blockedIP.keys())
            if(blockedIP[str] == ipIn)
                return;
    }
    clientIP.insert(name,ipIn);
    newPar(name);
}

void chatserver::serverCommands(QString name, QString command)
{
        QString nameAdmin = "ADMIN";
        command = command.remove('&');

        if(command.toUpper() == "SHUTDOWN")
        {
            QString shutDown = "Server is shutting down in THREE minutes!!!\nPlease log off now!!!";
            QTimer::singleShot(180000,this,SLOT(deleteLater()));
            emit toThread(nameAdmin, shutDown.toUtf8());
        }else if(command.toUpper() == "DIE")
        {
            QString dye = "Emergency server shutdown NOW!!\nPlease log off now!!!";
            QTimer::singleShot(2000,this,SLOT(deleteLater()));
            emit toThread(nameAdmin, dye.toUtf8());
        }else if(command.toUpper() == "YELLOW")
        {
            QHostAddress tempIP = clientIP[name];
            emit warnThread(name,command,tempIP);
        }
        else if(command.toUpper() == "RED3")
        {
            QHostAddress tempIP = clientIP[name];
            emit warnThread(name,command,tempIP);
            blockedIP.insert(name,tempIP);
        }
        else if(command.toUpper() == "RED1")
        {
            QHostAddress tempIP = clientIP[name];
            emit warnThread(name,command,tempIP);
            blockedIP.insert(name,tempIP);
            unblockList.push_back(name);
            QTimer::singleShot(600000,this,SLOT(unBlock()));
        }else if(command.toUpper() == "RED2")
        {
            QHostAddress tempIP = clientIP[name];
            emit warnThread(name,command,tempIP);
            blockedIP.insert(name,tempIP);
            unblockList.push_back(name);
            QTimer::singleShot(86400000,this,SLOT(unBlock()));
        }
}

void chatserver::unBlock()
{
    qDebug() << "REMOVING NAME NOW!! " << unblockList[0];
    blockedIP.remove(unblockList[0]);
    unblockList.remove(0);
}

void chatserver::newPar(QString name)
{
    QString greet = "SERVER: " + name + " has joined the chatroom!";
    QByteArray message = greet.toUtf8();
    data = message;
    emit toThread(name, message);
}

QString chatserver::qstringDatRet()
{
    QString temp(data);
    QDate date = QDate::currentDate();
    QString dateString = date.toString();
    QTime serverTime = QTime::currentTime();
    QString timeString = serverTime.toString();
    temp = "<Date: " + dateString + " Time: " + timeString + "> " + temp;
    logChat(temp,dateString);
    return temp;
}

void chatserver::sendToChat(QString sending)
{
    if(sending.isEmpty())
        return;
    QByteArray temp = "CHATTY " + sending.toUtf8();
    //socket->write(temp);
}

bool chatserver::checkForCommand(QString command, QString name)
{

    if(command.at(0) == '%')
    {
        clientCommands(command, name);

        return true;
    }
    else
        return false;
}

void chatserver::clientCommands(QString command, QString name)
{

    if(command.at(1).toUpper() == 'B')
    {
        leftChat(name);
        //return true;
    }
    //else
    //return false;
}

void chatserver::logChat(QString chats, QString currentDate)
{
    QString dateLog = currentDate + ".log";
    QFile log(dateLog);
    log.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&log);
    out << chats << endl;
}

void chatserver::leftChat(QString name)
{
    //qDebug() << "In left chat " << name;
    QString buhbye = "SERVER: " + name + " has left the chatroom!";
    QByteArray message = buhbye.toUtf8();
    data = message;
    emit toThread(name, message);
    clientIP.remove(name);
}
