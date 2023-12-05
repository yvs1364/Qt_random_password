#include "mainwindow.h"
#include "inputdialog.h"
#include <QFile>
#include <qDir>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow){
  QFontDatabase::addApplicationFont("D:/Dev/qt/QT_Random_Password/stratos-mediumitalic.otf");

  QFile file("D:/Dev/qt/QT_Random_Password/style.qss");
  if(file.open(QFile::ReadOnly)) {
    QString StyleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(StyleSheet);
  }


  pass = new Pass;
  ui->setupUi(this);
  fill_data();

  QAction *option = ui->menuBar->addAction("Option");
  connect(option, SIGNAL(triggered()), this, SLOT(clear_db()));

  connect(ui->add_manual,&QPushButton::clicked,this,&MainWindow::add_manual);
  connect(ui->delete_row,&QPushButton::clicked,this,&MainWindow::delete_row);
  connect(ui->show_pass->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex)),SLOT(edit_row(QModelIndex)));
  connect(ui->inject_pass,&QPushButton::clicked,this,&MainWindow::inject_pass);


  connect(ui->Generate,&QPushButton::clicked,this,[this](){
    ui->input_pass->setText(pass->generate());
  });
}

MainWindow::~MainWindow(){
  delete ui;
  delete pass;
}

void MainWindow::fill_data(){
  // Fill QTableView
  // ===============

  QSqlQuery query("SELECT * FROM pass");

  QStandardItemModel *model = new QStandardItemModel(0, 3, this);
  model->setHeaderData(1, Qt::Horizontal, "Pass", Qt::DisplayRole);
  model->setHeaderData(2, Qt::Horizontal, "Website", Qt::DisplayRole);
  while (query.next()){
    ui->show_pass->setModel(model);
    // set size of column
    ui->show_pass->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->show_pass->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    model->appendRow(QList<QStandardItem *>()
    << new QStandardItem(query.value("id").toString())
    << new QStandardItem(query.value("pass").toString())
    << new QStandardItem(query.value("website").toString()) );
    ui->show_pass->setColumnHidden(0, true);
  }
}

void MainWindow::add_manual(){
  QStringList list = InputDialog::getStrings(this);
  if (!list.isEmpty()) {
    pass->inject(list[0],list[1]);
    fill_data();
  }
}

void MainWindow::delete_row(){
  QStandardItemModel *model = new QStandardItemModel(0, 2, this);
  QItemSelection selection( ui->show_pass->selectionModel()->selection() );

  QList<int> rows;
  foreach( const QModelIndex & index, selection.indexes() ) {
    rows.append( index.row() );
  }

  std::sort(rows.begin(), rows.end());

  int prev = -1;
  int current;
  for( int i = rows.count() - 1; i >= 0; i -= 1 ) {
    current = rows[i];
    if( current != prev ) {
      model->removeRows( current, 1);
      prev = current;
    }
  }
  pass->delete_by_id(ui->show_pass->model()->index(current,0).data().toInt());
  fill_data();
  delete model;
}

void MainWindow::edit_row(const QModelIndex &iRow){
   int row = iRow.row();

  int id = ui->show_pass->model()->data(ui->show_pass->model()->index(row,0)).toInt();
  QString passValue = ui->show_pass->model()->data(ui->show_pass->model()->index(row,1)).toString();
  QString url = ui->show_pass->model()->data(ui->show_pass->model()->index(row,2)).toString();

  pass->update_data(QVariant(id).toString(),passValue,url);

}

void MainWindow::inject_pass(){
  QString inputPass =  ui->input_pass->toPlainText();
  QString inputUrl = ui->input_url->toPlainText();
  if(inputPass!="" && inputUrl!=""){
    pass->inject(inputPass,inputUrl);
    fill_data();
  }else{
    qInfo("Empty field!");
  }
}



void MainWindow::clear_db(){
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, "Delete data", "Are you sure to delete all data and quit ?",
  QMessageBox::Yes|QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    pass->clear_data();
    QApplication::quit();
  }
}


