#include "login.h"
#include "database.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
  bool devMode=true;
  QApplication a(argc, argv);
  Database db; // init db
//  if (devMode){
//    MainWindow w;
//    w.show();
//  }else {
    Login l;
    l.show();
//  }

  return a.exec();
}
