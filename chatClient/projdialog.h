#ifndef PROJDIALOG_H
#define PROJDIALOG_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class ProjDialog;
}

class ProjDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProjDialog(QWidget *parent = 0);
    ~ProjDialog();

public slots:
    void getChatName();
    
private:
    Ui::ProjDialog *ui;
};

#endif // PROJDIALOG_H
