#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QTableView>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QDebug>
#include <QHeaderView>

class TableWindow : public QTableView
{
public:
    TableWindow(QWidget *parent = nullptr);
    ~TableWindow();

    void ModelLoad();
    void AddPatient();
    void DeletePatient();

private:
    QSqlDatabase db;
    QSqlTableModel *model;
    int clmn_cnt = 0;
    int row_cnt = 0;
};

#endif // TABLEWINDOW_H
