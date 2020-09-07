#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << QCoreApplication::applicationDirPath() + "/my_db.db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/my_db.db");
    db.open();

    model = new QSqlTableModel(this);
    model->setTable("Patients");
    model->select();
    ui->tableView->setModel(model);

    qDebug() << model_index[0];
    this->clmn_cnt = model->columnCount();
    this->row_cnt = model->rowCount();

    tableHeader = ui->tableView->horizontalHeader();
    connect(tableHeader, SIGNAL(sectionClicked ( int ) ),
        this, SLOT(sortColumn ( int ) ));
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::on_actionAdd_triggered()
{
    this->row_cnt = model->rowCount();
    model->insertRow(row_cnt++);
    qDebug() << row_cnt;
}

void MainWindow::on_actionRemove_triggered()
{
    if( row_cnt != 1)
        model->removeRow(row_cnt-- - 1);
    qDebug() << row_cnt;
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{

}

void MainWindow::sortColumn(int logicalindex)
{
    qDebug() << logicalindex;
    model->sort(logicalindex, Qt::AscendingOrder);
}
