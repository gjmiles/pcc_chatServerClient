#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    chatName = "ADMIN";
    ui->setupUi(this);
//    setCentralWidget(ui->plainTextEdit);
    ui->plainTextEdit->setReadOnly(true);
    chatty.serverStart();
    //connect(ui->lineEdit,SIGNAL)
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(enterLine()));
    connect(&chatty,SIGNAL(toThread(QString,QByteArray)),this,SLOT(updateChat()));
    connect(this,SIGNAL(serverCommand(QString,QString)),&chatty,SLOT(serverCommands(QString,QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enterLine()
{
    QString line = ui->lineEdit->text();
    QString tempName = "";
    if(line.at(0) == '&')
    {
        if(line.mid(1).toUpper() != "SHUTDOWN" || line.mid(1).toUpper() != "DIE")
        {
            int space = line.indexOf(" ") + 1;
            tempName = line.mid(space);
            space = space - 1;
            line = line.mid(0,space);
            qDebug() << " warning name out " <<tempName;
        }
        emit serverCommand(tempName,line);
        ui->lineEdit->clear();
        line = "Server command: " + line;
        ui->plainTextEdit->appendPlainText(line);
        return;
    }
    if(line.isEmpty())
        return;
    QString space = " : ";
    line.insert(0,space);
    line.insert(0,chatName);
    chatty.dataToChat(chatName,line.toUtf8());
    ui->lineEdit->clear();
}
/*void chatdisplay()
{

}
*/

void MainWindow::updateChat()
{
    QString inChat = chatty.qstringDatRet();
    ui->plainTextEdit->appendPlainText(inChat);
}
