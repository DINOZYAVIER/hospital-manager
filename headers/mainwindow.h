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

    void on_tableView_doubleClicked(const QModelIndex &index);

    void sortColumn(int logicalindex);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    QModelIndex model_index[4];
    QHeaderView* tableHeader;
    int row_cnt = 0;
    int clmn_cnt = 0;
};
#endif // MAINWINDOW_H
