#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QDebug>
#include "../headers/tablewindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void AddTable(TableWindow *t);

private slots:
    void on_actionAdd_triggered();

    void on_actionRemove_triggered();

private:
    Ui::MainWindow *ui;
    TableWindow *t;
    QSqlDatabase db;
    QSqlTableModel *model;
};
#endif // MAINWINDOW_H
