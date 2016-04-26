#include <QtGui>
#include <QKeyEvent>
#include <QTimer>
#include <QDateTime>
#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "ui_projdialog.h"
//#include "projdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setCentralWidget(ui->plainTextEdit);
    ui->textEdit->setReadOnly(true);
    //connect(ui->lineEdit,SIGNAL()

    if(chatName.isEmpty())
    {
        ui->textEdit->append(tr("Please Enter your chat name! "));
        connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(getChatName()));
        connect(this,SIGNAL(giveName(QString)),&chatClient,SLOT(getName(QString)));
    }
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(enterLine()));
    connect(&chatClient,SIGNAL(incomingMessage()),this,SLOT(updateChat()));
    //connect(this,SIGNAL(destroyed()),&chatClient,SLOT(goodBye()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F1)
    {
        if(!chatName.isEmpty())
        {
            chatName = "";
            disconnect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(enterLine()));
            ui->textEdit->append(tr("Please Enter your chat name! "));
            connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(getChatName()));
            connect(this,SIGNAL(giveName(QString)),&chatClient,SLOT(getName(QString)));
            connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(enterLine()));
        }
    }else if(event->key() == Qt::Key_F2)
    {
        //chatName = "";
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->append(tr("Disconnected from server!"));
        ui->textEdit->setTextColor(Qt::black);
        chatClient.goodBye();
    }else if(event->key() == Qt::Key_F3)
    {
        disconnect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(enterLine()));
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->append(tr("What file name would you like to log chat to? \n To append to previous log simply re-enter log name."));
        ui->textEdit->setTextColor(Qt::black);
        connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(getFileName()));
        connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(enterLine()));
    }else if(event->key() == Qt::Key_F4){
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->append(tr("Stoping logging."));
        ui->textEdit->setTextColor(Qt::black);
        stopLog();
    }else if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_F10)
    {
        chatClient.goodBye();
        QTimer::singleShot(1000, qApp, SLOT(quit()));
    }

}

void MainWindow::enterLine()
{ 
    QString line = ui->lineEdit->text();
    if(line.isEmpty() || checkForCommand(line))
        return;
    QString space = " : ";
    line.insert(0,space);
    line.insert(0,chatName);
    chatClient.sendToServer(line);
    ui->lineEdit->clear();
}

void MainWindow::updateChat()
{
    QString inChat = chatClient.qstringDatRet();
    ui->textEdit->append(inChat);
    if(canLog)
        logChat(inChat);
}

/*void chatdisplay()
{

}
*/

/*
void MainWindow::on_actionNew_Window_triggered()
{
    //ProjDialog windowDial;
    //windowDial.setModal(true);
    //windowDial.exec();
    windowDial = new ProjDialog(this);
    windowDial->show();
}
*/


void MainWindow::getChatName()
{
    chatName = ui->lineEdit->text();
    if(chatName.isEmpty())
    {
       // QColor color = ui->textEdit->textColor();
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->append(tr("Please enter a chat name!!!"));
        return;
    }
    emit giveName(chatName);
    ui->textEdit->setTextColor(Qt::black);
    if(chatClient.clientStart())
        chatClient.sendToServer(chatName);
    else
        ui->textEdit->append(tr("Can not connect to server!"));
    //ui->textEdit->clear();
    ui->textEdit->append(tr("Hello %1 !").arg(chatName));
    //chatClient.clientStart();
    //setChatName(temp);
    ui->lineEdit->clear();
    disconnect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(getChatName()));
    disconnect(this,SIGNAL(giveName(QString)),&chatClient,SLOT(getName(QString)));
}

bool MainWindow::checkForCommand(QString command)
{
    //qDebug() << command.at(0);
    if(command.at(0) == '%')
    {
        if(!chatClient.commands(command))
        {
            ui->textEdit->setTextColor(Qt::red);
            ui->textEdit->append(tr("Messages prefaced with % are for commands!\nCommand not recognized"));
            ui->textEdit->setTextColor(Qt::black);

        }
        return true;
    }
    else
        return false;
}

void MainWindow::getFileName()
{
    logFile = ui->lineEdit->text();
    ui->lineEdit->clear();
    if(logFile.isEmpty())
    {
       // QColor color = ui->textEdit->textColor();
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->append(tr("Logging canceled! Need log file name!"));
        ui->textEdit->setTextColor(Qt::black);
        canLog = false;
        disconnect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(getFileName()));
        return;
    }
    ui->textEdit->setTextColor(Qt::red);
    ui->textEdit->append(tr("******\nNow Logging!\n******"));
    ui->textEdit->setTextColor(Qt::black);
    canLog = true;
    disconnect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(getFileName()));
}

void MainWindow::logChat(QString chats)
{
    QDate date = QDate::currentDate();
    QString dateString = date.toString();
    QTime clientTime = QTime::currentTime();
    QString timeString = clientTime.toString();
    chats = "<Date: " + dateString + " Time: " + timeString + "> " + chats;
    QString fileName = logFile + ".log";
    QFile log(fileName);
    log.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&log);
    out << chats << endl;
}

void MainWindow::stopLog()
    {
        canLog = false;
        logFile = "";
    }
/*
void MainWindow::setChatName(QString name)
{
    chatName = name;
}
*/
