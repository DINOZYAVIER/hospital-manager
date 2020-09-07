#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/my_db.db");
    db.open();

    model = new QSqlTableModel(this);
    model->setTable("Patients");
    model->select();
    ui->patientTable->setModel(model);

    recordsModel = new QSqlTableModel(this);
    recordsModel->setTable("ClinicalRecords");
    recordsModel->select();
    ui->recordTable->setModel(recordsModel);

    radiographsModel = new QSqlTableModel(this);
    radiographsModel->setTable("Radiographs");
    radiographsModel->select();
    ui->radiographTable->setModel(radiographsModel);

    this->clmn_cnt = model->columnCount();
    this->row_cnt = model->rowCount();

    tableHeader = ui->patientTable->horizontalHeader();
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
    model->insertRow(row_cnt);
    QModelIndex index = model->index(row_cnt, 0);
    if( !model->setData(index, row_cnt + 1) )
        qDebug() << "Did not manage to add new patient, as previous record is empty";
    else
        row_cnt++;
    qDebug() << row_cnt;
}

void MainWindow::on_actionRemove_triggered()
{
    if( row_cnt != 1)
        model->removeRow(row_cnt - 1);
    this->row_cnt--;
    qDebug() << row_cnt;
}

void MainWindow::sortColumn(int logicalindex)
{
    qDebug() << logicalindex;
    model->sort(logicalindex, Qt::AscendingOrder);
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{

}
