#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
QDialog(parent),
ui(new Ui::Login){
  ui->setupUi(this);
  w = new MainWindow();

  connect(ui->btn_login,&QPushButton::clicked,this,&Login::on_login);
}

Login::~Login(){
  delete ui;
  delete w;
}

bool Login::check_user(QString usr,QString pwd){
  m_query.exec("SELECT * FROM user WHERE username='"+usr+"'AND password='"+pwd+"'");
  if (m_query.first()) {
    return true;
  } else {
    return false;
  }
}

void Login::on_login(){
  QString usr = ui->lineEdit_username->text();
  QString pwd = ui->lineEdit_password->text();

  if(check_user(usr,pwd)){
    w->show();
    this->hide();
  } else{
    QMessageBox::warning(this,"Login","Error wrong login");
  }

}

