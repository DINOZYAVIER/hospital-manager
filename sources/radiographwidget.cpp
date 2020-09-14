#include "radiographwidget.h"
#include "ui_radiographwidget.h"

RadiographWidget::RadiographWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::RadiographWidget)
{
    m_ui->setupUi(this);

    connect( this, &RadiographWidget::constructSignal, this, &RadiographWidget::onConstruct );
    connect( this, &RadiographWidget::addRadiographSignal, this, &RadiographWidget::onAddRadiograph );
    connect( this, &RadiographWidget::removeRadiographSignal, this, &RadiographWidget::onRemoveRadiograph );
    connect( this, &RadiographWidget::displayRadiographsSignal, this, &RadiographWidget::onDisplayRadiographs );
}

RadiographWidget::~RadiographWidget()
{
    delete m_ui;
}

void RadiographWidget::onConstruct( QSqlDatabase db )
{
    m_db = db;

    m_radiographsModel = new QSqlTableModel( this );
    m_radiographsModel->setTable( "Radiographs" );
    m_radiographsModel->select();
}

void RadiographWidget::onAddRadiograph( int id )
{
    addRadiographDialog dial;
    dial.setModal(true);
    dial.exec();
    QVariant* data = dial.getData();

    QSqlRecord record( m_radiographsModel->record() );
    record.setValue( 0, QVariant() );
    record.setValue( 1, data[0] );
    record.setValue( 2, data[1] );
    record.setValue( 3, data[2] );
    record.setValue( 4, id );
    m_radiographsModel->insertRecord( -1, record );
    m_radiographsModel->submitAll();
    m_radiographsModel->select();
    qDebug() << "Added radiograph with ID:" << m_radiographsModel->record( m_radiographsModel->rowCount() - 1 ).field( 0 ).value().toInt();
}

void RadiographWidget::onRemoveRadiograph()
{

}

void RadiographWidget::onDisplayRadiographs( QVariant id )
{

}

