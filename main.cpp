#include "login.h"
#include "database.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Database db; // init db
    Login l;
    l.show();

    return a.exec();
}
