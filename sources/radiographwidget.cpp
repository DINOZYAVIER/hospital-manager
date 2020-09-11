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
}

void RadiographWidget::onAddRadiograph( int id )
{
    qDebug() << "Hello";
    addRadiographDialog dial;
    dial.setModal(true);
    dial.exec();

    QVariant* data = dial.getData();
    qDebug() << data[0] << data[1] << data[2];

    QSqlRecord record( m_radiographsModel->record() );
    record.setValue( 0, QVariant() );
    record.setValue( 1, "" );
    record.setValue( 2, QVariant( "01.01.1980" ) );
    record.setValue( 3, "" );
    record.setValue( 4, id );
    m_radiographsModel->insertRecord( -1, record );
    m_radiographsModel->submitAll();
    m_radiographsModel->select();
    qDebug() << "Added radiograph with ID:" << m_radiographsModel->record( m_radiographsModel->rowCount() - 1 ).field( 0 ).value().toInt();
}

void RadiographWidget::onRemoveRadiograph( )
{

}

void RadiographWidget::onDisplayRadiographs( QVariant id )
{

}

