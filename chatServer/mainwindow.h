#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "chatserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    //void chatdisplay();
    void enterLine();
    void updateChat();
    
signals:
    void serverCommand(QString name, QString command);

private:
    Ui::MainWindow *ui;
    chatserver chatty;
    QString chatName;

};

#endif // MAINWINDOW_H
