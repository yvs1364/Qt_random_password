#ifndef LOGIN_H
#define LOGIN_H

#include "mainwindow.h"
#include <QDialog>
#include <QMessageBox>

namespace Ui {class Login;}

class Login : public QDialog{
  Q_OBJECT

public:
  QSqlQuery m_query;
  explicit Login(QWidget *parent = nullptr);
  ~Login();
  bool check_user(QString usr,QString pwd);

private slots:
  void on_login();

private:
  Ui::Login *ui;
  MainWindow *w;

};

#endif // LOGIN_H
