#include "database.h"

Database::Database(){
  create_passManager_table();
}

QSqlDatabase Database::get_m_db(){
  return m_db;
}

void Database::create_passManager_table(){
  // Create Pass db SQLITE
  // =============
  if (QSqlDatabase::isDriverAvailable("QSQLITE")){
    m_db.setDatabaseName(m_path_db);

    if (m_db.open()){
      try {
        m_query.exec("CREATE TABLE pass (id INTEGER PRIMARY KEY, pass TEXT, website TEXT, unique (pass, website))");
        m_query.exec("CREATE TABLE user (id INTEGER PRIMARY KEY, username TEXT, password TEXT, unique (username, password))");
      } catch (...) {
        qDebug("Table not created!");
      }
    }else{
      qDebug("Dirver not available!");
    }
  }
}
