#include "patientrecordwidget.h"
#include "ui_patientrecordwidget.h"

PatientRecordWidget::PatientRecordWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::PatientRecordWidget)
{
   m_ui->setupUi(this);

   connect( this, &PatientRecordWidget::addRecordSignal, this, &PatientRecordWidget::onAddRecord );
   connect( this, &PatientRecordWidget::removeRecordSignal, this, &PatientRecordWidget::onRemoveRecord );
   connect( this, &PatientRecordWidget::displayRecordsSignal, this, &PatientRecordWidget::onDisplayRecords );
   connect( this, &PatientRecordWidget::constructSignal, this, &PatientRecordWidget::onConstruct );

}

PatientRecordWidget::~PatientRecordWidget()
{
    delete m_ui;
}

void PatientRecordWidget::onConstruct ( QSqlDatabase db)
{
    m_db = db;

    m_recordsModel = new QSqlTableModel( this );
    m_recordsModel->setTable( "ClinicalRecords" );
    m_recordsModel->select();
    m_ui->recordTable->setModel( m_recordsModel );
    m_ui->recordTable->hideColumn(4);
}

void PatientRecordWidget::onAddRecord( int id )
{
    qDebug() << "HELLO" << m_recordsModel->rowCount();
    AddRecordDialog dial;
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
        //m_radiographsModel->select();
        qDebug() << "Removed record with ID:" << id;
    }
}

void PatientRecordWidget::onDisplayRecords( QVariant id )
{
    qDebug() << id;
    m_recordsModel->setFilter("PatientID='" + id.toString() + "'");
}
