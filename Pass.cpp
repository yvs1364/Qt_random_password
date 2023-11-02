#include "Pass.h"

Pass::Pass(){ create_table(); }

Pass::~Pass(){}

std::string Pass::generate(){
  srand(time(NULL));
  int randNum;
  std::string finalPwd;
  for (int i = 0; i < m_passLength; i++) {
    randNum = rand() % m_allChar.length() + 1;
    finalPwd += m_allChar[randNum];
  }
  return finalPwd ;
}

void Pass::create_table(){
  // Create SQLITE
  // =============
  if (QSqlDatabase::isDriverAvailable("QSQLITE")){
    m_db.setDatabaseName(m_path);

    if (m_db.open()){
      try {
        m_query.exec("CREATE TABLE pass (id INTEGER PRIMARY KEY, pass TEXT, website TEXT, unique (pass, website))");
      } catch (...) {
        qDebug("Table not created!");
      }
    }else{
      qDebug("Dirver not available!");
    }
  }
}
void Pass::inject(QString pass,QString url){
  // Inject SQLITE
  // =============
  if (m_db.open()){
    try {
      m_query.exec("INSERT INTO pass(pass, website) VALUES('"+pass+"','"+url+"')");
    } catch (...) {
      qFatal("Error data not added!");
    }

  }else{
    qDebug("DB not open!");
  }
}

//void Pass::inject(QString pass){
//  // Setup the model
//  QSqlTableModel *model = new QSqlTableModel();
//  model->setTable("pass");
//  model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//  model->select(); // will populate the model

////   Insert new row and data
//  const int row = model->rowCount();

//  model->insertRows(row, 1);
//  model->setData(model->index(row, 1), pass);
//  model->setData(model->index(row, 2), "Second column value");
//  // Commit the new record into database
//  model->submitAll(); // submit

//  model->select();
//}

void Pass::clear_data(){
  // Delete data
  // =============

  if (m_db.open()){
    try {
      m_query.exec("DELETE FROM pass");
    } catch (...) {
      qFatal("Error data not cleared!");
    }

  }else{
    qDebug("DB not open!");
  }
}
