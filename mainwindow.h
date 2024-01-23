#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qDebug>
#include <QAbstractItemModel>
#include <QMessageBox>
#include <ui_mainwindow.h>
#include "Pass.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void fill_data();

private slots:
  void add_manual();
  void delete_row();
  void edit_row(const QModelIndex &iRow);
  void inject_pass();
  void clear_db();

private:
  Ui::MainWindow *ui;
  Pass *pass;
};
#endif // MAINWINDOW_H
