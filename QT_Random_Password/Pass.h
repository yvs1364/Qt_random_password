#ifndef PASS_H
#define PASS_H
#include <QDebug>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QtDebug>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <QStandardItemModel>
#include <sstream>
#include <QSqlTableModel>

class Pass{
    private:
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery m_query;
    QString m_path = "C:/sqlite/pass.db";
    std::string m_allChar = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN0123456789=+-*.?,;:!%#@";
    int m_passLength = 12;


    public:
    Pass();
    ~Pass();
    std::string generate();
    void create_table();
    void fill_data();
    void inject(QString pass,QString url);
    void clear_data();
};

#endif // GENERATE_PASS_H
