#include "../headers/tablewindow.h"

TableWindow::TableWindow(QWidget *parent)
    : QTableView(parent)
{
    ModelLoad();
}

TableWindow::~TableWindow()
{
    delete model;
}

void TableWindow::ModelLoad()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/dinozyavier/hospital/my_db.db");
    db.open();

    if( !db.isOpen() )
        qDebug() << "fukup";
    else
    {
        model = new QSqlTableModel(this);
        model->setTable("Patients");
        model->select();
        this->setModel(model);

        this->verticalHeader()->setVisible(false);
        this->resizeColumnsToContents();
        this->resizeRowsToContents();
        this->clmn_cnt = model->columnCount();
        this->row_cnt = model->rowCount();
        int x = 0,
            y = 0;

         for (int i = 0; i < clmn_cnt; ++i)
             x+= this->columnWidth(i);

         y += 5 * this->rowHeight(0);


        this->setFixedSize(x, y);
        //qDebug() << this->isColumnHidden(1) << this->isRowHidden(1) << model->columnCount() << model->rowCount();
    }
}

void TableWindow::AddPatient()
{
    //model->insertRow(row_cnt);
    model->insertRow(model->rowCount(QModelIndex()));
}

void TableWindow::DeletePatient()
{
    qDebug() << row_cnt;
    if( row_cnt != 1)
        model->removeRows( row_cnt--, 1 );
}












