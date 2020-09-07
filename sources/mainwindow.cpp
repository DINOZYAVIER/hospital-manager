#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/dinozyavier/hospital/my_db.db");
    db.open();

    model = new QSqlTableModel(this);
    model->setTable("Patients");
    model->select();
    ui->tableView->setModel(model);

    this->clmn_cnt = model->columnCount();
    this->row_cnt = model->rowCount();

}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::on_actionAdd_triggered()
{
    model->insertRow(row_cnt++);
    qDebug() << row_cnt;
}

void MainWindow::on_actionRemove_triggered()
{
    if( row_cnt != 1)
        model->removeRow(row_cnt-- - 1);
}
