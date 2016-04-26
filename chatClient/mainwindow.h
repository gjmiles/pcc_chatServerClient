#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "projdialog.h"
#include "client.h"
#include "ui_mainwindow.h"


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setChatName(QString name);
    bool checkForCommand(QString command);
    void logChat(QString chats);
    void stopLog();

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    //void chatdisplay();

private slots:
    //void on_actionNew_Window_triggered();
    void getChatName();
    void enterLine();
    void updateChat();
    void getFileName();

signals:
    void giveName(QString name);

private:
    Ui::MainWindow *ui;
    //ProjDialog *windowDial;
    //Ui::ProjDialog *ui;
    client chatClient;
    QString chatName;
    QString logFile;
    bool canLog = false;
};

#endif // MAINWINDOW_H
