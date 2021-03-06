#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow){
    ui->setupUi(this);
    connect(ui->SiginButton,SIGNAL(clicked()),this,SLOT(SLOT_LoginButtonClicked()));
    connect(ui->QuitButton, SIGNAL(clicked()),this,SLOT(SLOT_QuitButtonClicked()));
}

LoginWindow::~LoginWindow(){
    delete ui;
}

void LoginWindow::SLOT_LoginButtonClicked(){
    if(ui->UsernameEditor->text().toUtf8() == ""){
        QMessageBox::warning(this,tr("Warning"),tr("Please type in your username."),QMessageBox::Yes);
        return;
    }
    if(ui->PasswordEditor->text().toUtf8() == ""){
        QMessageBox::warning(this,tr("Warning"),tr("Please type in correct password."),QMessageBox::Yes); // Did I get something wrong here?
        return;
    }
    bzero((void*)&Data,sizeof(LoginData));
    memcpy((void*)&(Data.UserName),ui->UsernameEditor->text().toUtf8().data(),ui->UsernameEditor->text().length());
    memcpy((void*)&(Data.PassWord),ui->PasswordEditor->text().toUtf8().data(),ui->PasswordEditor->text().length());
    emit SIGN_LoginStart(Data);
}

void LoginWindow::SLOT_QuitButtonClicked(){
    emit SIGN_QuitButtonClicked();
}
