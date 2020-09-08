#include "precompiled.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow(parent)
    , m_ui( new Ui::MainWindow )
{
    m_ui->setupUi( this );
    m_db = QSqlDatabase::addDatabase( "QSQLITE" );
    m_db.setDatabaseName( QCoreApplication::applicationDirPath() + "/HospitalDB.db" );
    m_db.open();

    m_patientsModel = new QSqlTableModel( this );
    m_patientsModel->setTable( "Patients" );
    m_patientsModel->select();
    m_ui->patientTable->setModel( m_patientsModel );

    m_recordsModel = new QSqlTableModel( this );
    m_recordsModel->setTable( "ClinicalRecords" );
    m_recordsModel->select();
    m_ui->recordTable->setModel( m_recordsModel );

    m_radiographsModel = new QSqlTableModel( this );
    m_radiographsModel->setTable( "Radiographs" );
    m_radiographsModel->select();
    m_ui->radiographTable->setModel( m_radiographsModel );

    connect( m_ui->aAddPatient, &QAction::triggered, this, &MainWindow::onAddPatient );
    connect( m_ui->aRemovePatient, &QAction::triggered, this, &MainWindow::onRemovePatient );

    auto* header = m_ui->patientTable->horizontalHeader();
    connect( header, &QHeaderView::sortIndicatorChanged, this, &MainWindow::sortPatients );
}

MainWindow::~MainWindow()
{
    delete m_ui;
    m_db.close();
}

void MainWindow::onAddPatient()
{
    QSqlRecord record( m_patientsModel->record() );
    record.setValue( 0, QVariant() );
    record.setValue( 1, "" );
    record.setValue( 2, QVariant( "01.01.1980" ) );
    m_patientsModel->insertRecord( -1, record );
    m_patientsModel->submitAll();
    m_patientsModel->select();
    qDebug() << "Added patient with ID:" << m_patientsModel->record( m_patientsModel->rowCount() - 1 ).field( 0 ).value().toInt();
}

void MainWindow::onRemovePatient()
{
    auto currentIndex = m_ui->patientTable->selectionModel()->currentIndex();
    if( currentIndex.isValid() )
    {
        int id = m_patientsModel->record( currentIndex.row() ).field( 0 ).value().toInt();
        m_patientsModel->removeRow( currentIndex.row() );
        m_patientsModel->submitAll();
        m_patientsModel->select();
        qDebug() << "Removed patient with ID:" << id;
    }
}

void MainWindow::sortPatients( int index, Qt::SortOrder order )
{
    qDebug() << "Sort " << index << order;
    m_patientsModel->sort( index, order );
}
