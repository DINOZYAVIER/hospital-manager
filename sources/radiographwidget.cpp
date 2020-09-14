#include "radiographwidget.h"
#include "ui_radiographwidget.h"

RadiographWidget::RadiographWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::RadiographWidget)
{
    m_ui->setupUi(this);
    m_ui->imageLabel->setScaledContents(true);

    connect( this, &RadiographWidget::constructSignal, this, &RadiographWidget::onConstruct );
    connect( this, &RadiographWidget::addRadiographSignal, this, &RadiographWidget::onAddRadiograph );
    connect( this, &RadiographWidget::removeRadiographSignal, this, &RadiographWidget::onRemoveRadiograph );
    connect( this, &RadiographWidget::displayRadiographsSignal, this, &RadiographWidget::onDisplayRadiograph );
    connect( this, &RadiographWidget::nextRadiographSignal, this, &RadiographWidget::onDisplayNext );
    connect( this, &RadiographWidget::prevRadiographSignal, this, &RadiographWidget::onDisplayPrev );

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

void RadiographWidget::onDisplayRadiograph( QVariant id )
{
    qDebug() << "display radiograph";
    m_current_id = 0;
    m_radiographsModel->setFilter("RecordID='" + id.toString() + "'");
    qDebug() << m_radiographsModel->rowCount();

    m_ui->DateEdit->setText( m_radiographsModel->record( m_current_id ).field( "Date" ).value().toString() );
    m_ui->DescriptionEdit->setText( m_radiographsModel->record( m_current_id ).field( "Description" ).value().toString() );

    QByteArray data = m_radiographsModel->record( m_current_id ).field( "Radiograph" ).value().toByteArray();

    QPixmap mpixmap = QPixmap();
    if( mpixmap.loadFromData( data ))
    {
        qDebug() << "Radiograph number" << m_current_id + 1 << "for the record number" << id.toInt();
        m_ui->imageLabel->setPixmap(( mpixmap ));
    }
}

void RadiographWidget::onDisplayNext()
{
    qDebug() << "RadiographWidget::onDisplayNext()";
    if( m_current_id < m_radiographsModel->rowCount() )
    {
        ++m_current_id;
        m_ui->DateEdit->setText( m_radiographsModel->record( m_current_id ).field( "Date" ).value().toString() );
        m_ui->DescriptionEdit->setText( m_radiographsModel->record( m_current_id ).field( "Description" ).value().toString() );
        QByteArray data = m_radiographsModel->record( m_current_id ).field( "Radiograph" ).value().toByteArray();
        QPixmap mpixmap = QPixmap();
        if( mpixmap.loadFromData( data ))
        {
            qDebug() << "SUCCESS+";
            m_ui->imageLabel->setPixmap(( mpixmap ));
        }
    }
}

void RadiographWidget::onDisplayPrev()
{
    qDebug() << "RadiographWidget::onDisplayPrev()";
    if( m_current_id > 0 )
    {
        --m_current_id;
        m_ui->DateEdit->setText( m_radiographsModel->record( m_current_id ).field( "Date" ).value().toString() );
        m_ui->DescriptionEdit->setText( m_radiographsModel->record( m_current_id ).field( "Description" ).value().toString() );
        QByteArray data = m_radiographsModel->record( m_current_id ).field( "Radiograph" ).value().toByteArray();
        QPixmap mpixmap = QPixmap();
        if( mpixmap.loadFromData( data ))
        {
            //mpixmap.scaledToWidth( m_ui->imageLabel->width(), Qt::SmoothTransformation );
            qDebug() << "SUCCESS-";
            m_ui->imageLabel->setPixmap(( mpixmap ));
        }
    }
}
