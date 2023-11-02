#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qDebug>
#include <QAbstractItemModel>
#include <QMessageBox>
#include "Pass.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void fill_data();

    private slots:
    void on_Generate_clicked();

    void on_injectPass_clicked();

    void on_actionClear_db_triggered();

private:
    Ui::MainWindow *ui;
    Pass *pass;
};
#endif // MAINWINDOW_H
