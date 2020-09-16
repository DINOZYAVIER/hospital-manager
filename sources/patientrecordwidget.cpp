#include "patientrecordwidget.h"
#include "ui_patientrecordwidget.h"

PatientRecordWidget::PatientRecordWidget( QWidget *parent ) :
    QWidget( parent ),
    m_ui( new Ui::PatientRecordWidget )
{
   m_ui->setupUi( this );

   connect( this, &PatientRecordWidget::addRecordSignal, this, &PatientRecordWidget::onAddRecord );
   connect( this, &PatientRecordWidget::removeRecordSignal, this, &PatientRecordWidget::onRemoveRecord );
   connect( this, &PatientRecordWidget::displayRecordsSignal, this, &PatientRecordWidget::onDisplayRecords );
   connect( this, &PatientRecordWidget::constructSignal, this, &PatientRecordWidget::onConstruct );
   connect( this, &PatientRecordWidget::addRadiographSignal, this, &PatientRecordWidget::onAddRadiograph );
   connect( this, &PatientRecordWidget::removeRadiographSignal, this, &PatientRecordWidget::onRemoveRadiograph );
   connect( m_ui->recordTable, &QTableView::clicked, this, &PatientRecordWidget::onDisplayRadiographs );
   connect( this, &PatientRecordWidget::displayNextRadiographSignal, this, &PatientRecordWidget::onDisplayNext );
   connect( this, &PatientRecordWidget::displayPrevRadiographSignal, this, &PatientRecordWidget::onDisplayPrev );
   connect( m_ui->recordTable, &QTableView::clicked, this, &PatientRecordWidget::onRecordClicked );

}

PatientRecordWidget::~PatientRecordWidget()
{
    delete m_ui;
}

void PatientRecordWidget::onConstruct ( QSqlDatabase db )
{
    m_db = db;
    emit m_ui->radiographsWidget->constructSignal ( db );

    m_recordsModel = new QSqlRelationalTableModel( this );
    m_recordsModel->setTable( "ClinicalRecords" );
    m_recordsModel->select();
    m_ui->recordTable->setModel( m_recordsModel );
    m_recordsModel->setRelation( 4, QSqlRelation("Patients", "id", "Full_name" ));
    //m_ui->recordTable->hideColumn(4);
}

void PatientRecordWidget::onAddRecord( int id )
{
    AddRecordDialog dial;
    dial.setModal(true);
    dial.exec();
    QVariant* data = dial.getData();

    QSqlRecord record( m_recordsModel->record() );
    record.setValue( 0, QVariant() );
    record.setValue( 1, data[0] );
    record.setValue( 2, data[1] );
    record.setValue( 3, data[2] );
    record.setValue( 4, id );
    m_recordsModel->insertRecord( -1, record );
    m_recordsModel->submitAll();
    m_recordsModel->select();
    qDebug() << "Added record with ID:" << m_recordsModel->record( m_recordsModel->rowCount() - 1 ).field( 0 ).value().toInt();
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
    }
}

void PatientRecordWidget::onDisplayRecords( QVariant id )
{
    qDebug() << id;
    m_recordsModel->setFilter("PatientID='" + id.toString() + "'");
    m_ui->radiographsWidget->displayClear();
}

void PatientRecordWidget::onAddRadiograph()
{
    auto currentIndex = m_ui->recordTable->selectionModel()->currentIndex();
    int id = m_recordsModel->record( currentIndex.row() ).field( 0 ).value().toInt();
    emit m_ui->radiographsWidget->addRadiographSignal( id );
}

void PatientRecordWidget::onRemoveRadiograph()
{
    emit m_ui->radiographsWidget->removeRadiographSignal();
}

void PatientRecordWidget::onDisplayRadiographs()
{
    auto currentIndex = m_ui->recordTable->selectionModel()->currentIndex();
    QVariant id = m_recordsModel->record( currentIndex.row() ).field( 0 ).value().toInt();
    if( currentIndex.isValid() )
    {
        emit m_ui->radiographsWidget->recordClickedSignal( id.toInt() );
        emit m_ui->radiographsWidget->displayRadiographsSignal( id );
    }

    qDebug() << id;
}

void PatientRecordWidget::onDisplayNext()
{
    emit m_ui->radiographsWidget->nextRadiographSignal();
}

void PatientRecordWidget::onDisplayPrev()
{
    emit m_ui->radiographsWidget->prevRadiographSignal();
}

void PatientRecordWidget::onRecordClicked()
{

}
