#include "Pass.h"

Pass::Pass(){}

Pass::~Pass(){}

QString Pass::generate(){
  srand(time(NULL));
  int randNum;
  QString finalPwd;
  for (int i = 0; i < m_passLength; i++) {
    randNum = rand() % m_allChar.length() + 1;
    finalPwd += m_allChar[randNum];
  }
  return finalPwd ;
}


void Pass::inject(QString pass,QString url){
  // Inject SQLITE
  // =============
  try {
    m_query.exec("INSERT INTO pass(pass, website) VALUES('"+pass+"','"+url+"')");
  } catch (...) {
    qFatal("Error data not added!");
  }
}


void Pass::clear_data(){
  // Delete data
  // =============
  try {
    m_query.exec("DELETE FROM pass");
  } catch (...) {
    qFatal("Error data not cleared!");
  }
}
void Pass::delete_by_id(int id){
  try {
    m_query.exec("DELETE FROM pass where id='"+QString::number(id)+"'");
  } catch (...) {
    qFatal("Error data not cleared!");
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
