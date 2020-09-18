#include "precompiled.h"
#include "patientrecordwidget.h"
#include "ui_patientrecordwidget.h"

PatientRecordWidget::PatientRecordWidget( QWidget *parent ) :
    QWidget( parent ),
    m_ui( new Ui::PatientRecordWidget )
{
    m_ui->setupUi( this );

    m_recordsModel = new QSqlRelationalTableModel( this );
    m_recordsModel->setTable( "ClinicalRecords" );
    m_recordsModel->select();
    m_ui->recordTable->setModel( m_recordsModel );
    m_recordsModel->setRelation( 4, QSqlRelation( "Patients", "id", "Full_name") );

    connect( this, &PatientRecordWidget::displayRecordsSignal, this, &PatientRecordWidget::onDisplayRecords );
    connect( m_ui->recordTable, &QTableView::clicked, this, &PatientRecordWidget::onDisplayRadiographs );
}

PatientRecordWidget::~PatientRecordWidget()
{
    delete m_ui;
}

void PatientRecordWidget::onAddRecord()
{
    qDebug() << "hello";
    AddRecordDialog dialogWnd;
    dialogWnd.setWindowTitle( "Add record" );
    dialogWnd.setModal( true );
    if( dialogWnd.exec() == QDialog::Accepted )
    {
        qDebug() << dialogWnd.description() << dialogWnd.dateIn() << dialogWnd.dateOut();
        QSqlRecord record( m_recordsModel->record() );
        record.setValue( 0, QVariant() );
        record.setValue( 1, dialogWnd.description() );
        record.setValue( 2, dialogWnd.dateIn() );
        record.setValue( 3, dialogWnd.dateOut() );
        record.setValue( 4, m_current_id );
        m_recordsModel->insertRecord( -1, record );
        m_recordsModel->submitAll();
        m_recordsModel->select();
        qDebug() << "Added record with ID:" << m_recordsModel->record( m_recordsModel->rowCount() - 1 ).field( 0 ).value().toInt();
    }
}

void PatientRecordWidget::onRemoveRecord()
{
    auto currentIndex = m_ui->recordTable->selectionModel()->currentIndex();
    if( currentIndex.isValid() )
    {
        int id = m_recordsModel->record( currentIndex.row() ).field( 0 ).value().toInt();
        m_recordsModel->removeRow( currentIndex.row() );
        m_recordsModel->submitAll();
        m_recordsModel->select();
        qDebug() << "Removed record with ID:" << id;
        m_ui->radiographsWidget->displayClear();
    }
}

void PatientRecordWidget::onDisplayRecords()
{
    m_ui->radiographsWidget->setCurrentID( m_current_id );
    m_recordsModel->setFilter("PatientID='" + m_current_id.toString() + "'");
    m_ui->radiographsWidget->displayClear();
}

void PatientRecordWidget::onDisplayRadiographs()
{
    auto currentIndex = m_ui->recordTable->selectionModel()->currentIndex();
    QVariant id = m_recordsModel->record( currentIndex.row() ).field( 0 ).value().toInt();
    if( currentIndex.isValid() )
    {
        ActionStore::action( aAddRecord )->setEnabled( true );
        ActionStore::action( aRemoveRecord )->setEnabled( true );
        ActionStore::action( aAddRadiograph )->setEnabled( true );
        ActionStore::action( aRemoveRadiograph )->setEnabled( true );

        m_ui->radiographsWidget->setCurrentID( id );
        emit m_ui->radiographsWidget->displayRadiographsSignal();
    }

    else
    {
        ActionStore::action( aAddRecord )->setEnabled( false );
        ActionStore::action( aRemoveRecord )->setEnabled( false );
        ActionStore::action( aAddRadiograph )->setEnabled( false );
        ActionStore::action( aRemoveRadiograph )->setEnabled( false );
    }
}

void PatientRecordWidget::setAction()
{
    connect( ActionStore::action( aAddRecord ), &QAction::triggered, this, &PatientRecordWidget::onAddRecord );
    connect( ActionStore::action( aRemoveRecord ), &QAction::triggered, this, &PatientRecordWidget::onRemoveRecord );
    m_ui->radiographsWidget->setAction();
}

void PatientRecordWidget::openDB()
{
    m_recordsModel->setTable( "ClinicalRecords" );
    m_recordsModel->select();
    m_ui->recordTable->setModel( m_recordsModel );
    m_recordsModel->setRelation( 4, QSqlRelation( "Patients", "id", "Full_name") );
    m_ui->radiographsWidget->openDB();
}

void PatientRecordWidget::closeDB()
{
    m_recordsModel->clear();
    m_ui->radiographsWidget->closeDB();
}


