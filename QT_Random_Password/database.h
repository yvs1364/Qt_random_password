#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>

class Database{
private:
  QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
  QSqlQuery m_query;
  QString m_path_db = "C:/sqlite/passManager.db";

public:
  Database();
  void create_passManager_table();
  QSqlDatabase get_m_db();
};

#endif // DATABASE_H
