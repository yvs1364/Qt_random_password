#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    pass = new Pass;
    ui->setupUi(this);
    fill_data();

}

MainWindow::~MainWindow(){
    delete ui;
    delete pass;
}

void MainWindow::fill_data(){
  // Fill QTableView
  // ===============

  QSqlQuery query("SELECT * FROM pass");

  QStandardItemModel *model = new QStandardItemModel(0, 2, this);
  model->setHeaderData(0, Qt::Horizontal, "Pass", Qt::DisplayRole);
  model->setHeaderData(1, Qt::Horizontal, "Website", Qt::DisplayRole);
  while (query.next()){
    ui->showPass->setModel(model);
    // set size of column
    ui->showPass->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->showPass->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    model->appendRow(QList<QStandardItem *>() << new QStandardItem(query.value("pass").toString())
    << new QStandardItem(query.value("website").toString()));
  }
}

void MainWindow::on_Generate_clicked(){
  ui->input_pass->setText(QString::fromStdString(pass->generate()));
}

void MainWindow::on_injectPass_clicked(){
  QString inputPass =  ui->input_pass->toPlainText();
  QString inputUrl = ui->input_url->toPlainText();
  if(inputPass!="" && inputUrl!=""){
    pass->inject(inputPass,inputUrl);
    fill_data();
  }else{
    qInfo("Empty field!");
  }
}


void MainWindow::on_actionClear_db_triggered(){

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Test", "Are you sure to delete all data and quit ?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      qDebug() << "Yes was clicked";
      pass->clear_data();
      QApplication::quit();
    } else {
      qDebug() << "Yes was *not* clicked";
    }
}

