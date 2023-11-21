#ifndef PASS_H
#define PASS_H

#include <QDebug>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <time.h>
#include <QStandardItemModel>

class Pass{
    private:
    QSqlQuery m_query;
    QString m_allChar = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN0123456789=+-*.?,;:!%#@";
    int m_passLength = 12;

    public:
    Pass();
    ~Pass();
    QString generate();
    void fill_data();
    void inject(QString pass,QString url);
    void clear_data();
    void delete_by_id(int id);
};

#endif // GENERATE_PASS_H
