#include "projdialog.h"
#include "ui_projdialog.h"

ProjDialog::ProjDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjDialog)
{
    ui->setupUi(this);
    connect(ui->acceptButton,SIGNAL(clicked()),this,SLOT(getChatName()));
}

ProjDialog::~ProjDialog()
{
    delete ui;
}

void ProjDialog::getChatName()
{
    QString temp;
    temp = ui->lineEdit->text();
    if(temp.isEmpty())
        temp = "Biff";
    //setChatName(temp);
}
