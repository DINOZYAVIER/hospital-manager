#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../headers/main.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAdd_triggered();

    void on_actionRemove_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    int row_cnt = 0;
    int clmn_cnt = 0;
};
#endif // MAINWINDOW_H
