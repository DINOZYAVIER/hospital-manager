#include "precompiled.h"
#include "radiographwidget.h"
#include "ui_radiographwidget.h"

//extern ActionStore& as;

RadiographWidget::RadiographWidget( QWidget *parent ) :
    QWidget( parent ),
    m_ui( new Ui::RadiographWidget ),
    m_current_id( -1 )
{
    m_ui->setupUi( this );
    m_ui->imageLabel->setScaledContents( true );

    m_radiographsModel = new QSqlTableModel( this );
    m_radiographsModel->setTable( "Radiographs" );
    m_radiographsModel->select();

    /*ActionStore& as = ActionStore::get_instance();
    connect( this, &RadiographWidget::displayRadiographsSignal, this, &RadiographWidget::onDisplayRadiograph );
    connect( m_ui->DescriptionEdit, &QTextEdit::textChanged, this, &RadiographWidget::onUpdateInfo );
    connect( m_ui->DateEdit, &QTextEdit::textChanged, this, &RadiographWidget::onUpdateInfo );
    connect( this, &RadiographWidget::recordClickedSignal, this, &RadiographWidget::onRecordClicked );
    connect( m_ui->addRadiographButton, &QAbstractButton::clicked, this, &RadiographWidget::onAddRadiograph );
    connect( as.action( aRemovePatient ), &QAction::triggered, this, &RadiographWidget::onRemoveRadiograph );
    connect( as.action( aPrevRadiograph ), &QAction::triggered, this, &RadiographWidget::onDisplayNext );
    connect( as.action( aNextRadiograph ), &QAction::triggered, this, &RadiographWidget::onDisplayPrev );*/
}

RadiographWidget::~RadiographWidget()
{
    delete m_ui;
}

void RadiographWidget::onAddRadiograph()
{
    if( m_current_id >= 0 )
    {
        QString fileName = QFileDialog::getOpenFileName( this,
            tr( "Open Image" ), QCoreApplication::applicationDirPath(), tr( "Image Files (*.png *.jpg *.bmp)" ) );

        QFile file( fileName );
        if ( !file.open( QIODevice::ReadOnly ) )
            return;
        QByteArray inByteArray = file.readAll();

        QSqlRecord record( m_radiographsModel->record() );
        record.setValue( 0, QVariant() );
        record.setValue( 1, "" );
        record.setValue( 2, "" );
        record.setValue( 3, inByteArray );
        record.setValue( 4, m_current_id );
        m_radiographsModel->insertRecord( -1, record );
        m_radiographsModel->submitAll();
        m_radiographsModel->select();
        qDebug() << "Added radiograph with ID:" << m_radiographsModel->record( m_radiographsModel->rowCount() - 1 ).field( 0 ).value().toInt();
    }
}

void RadiographWidget::onRemoveRadiograph()
{
    if( m_current_radiograph >= 0 && m_current_radiograph < m_radiographsModel->rowCount() )
    {
        int id = m_radiographsModel->record( m_current_radiograph ).field( 0 ).value().toInt();
        m_radiographsModel->removeRow( m_current_radiograph );
        m_radiographsModel->submitAll();
        m_radiographsModel->select();
        qDebug() << "Removed radiograph with ID:" << id;
        displayClear();
    }
}

void RadiographWidget::onDisplayRadiograph( QVariant id )
{
    m_current_radiograph = 0;
    m_radiographsModel->setFilter("RecordID='" + id.toString() + "'");
    qDebug() << m_radiographsModel->rowCount();

    if( m_radiographsModel->rowCount() > 0)
    {
        m_ui->DateEdit->setText( m_radiographsModel->record( m_current_radiograph ).field( "Date" ).value().toString() );
        m_ui->DescriptionEdit->setText( m_radiographsModel->record( m_current_radiograph ).field( "Description" ).value().toString() );

        QByteArray data = m_radiographsModel->record( m_current_radiograph ).field( "Radiograph" ).value().toByteArray();

        QPixmap mpixmap = QPixmap();
        if( mpixmap.loadFromData( data ))
        {
            qDebug() << "Radiograph number:" << m_current_radiograph + 1 << "with record number:" << id.toInt();
            m_ui->imageLabel->setPixmap(( mpixmap ));
        }
    }
    else
        displayClear();
}

void RadiographWidget::onDisplayNext()
{
    if( m_current_radiograph >= 0 && m_current_radiograph < m_radiographsModel->rowCount() - 1 )
    {
        ++m_current_radiograph;
        m_ui->DateEdit->setText( m_radiographsModel->record( m_current_radiograph ).field( "Date" ).value().toString() );
        m_ui->DescriptionEdit->setText( m_radiographsModel->record( m_current_radiograph ).field( "Description" ).value().toString() );
        QByteArray data = m_radiographsModel->record( m_current_radiograph ).field( "Radiograph" ).value().toByteArray();
        QPixmap mpixmap = QPixmap();
        if( mpixmap.loadFromData( data ))
            m_ui->imageLabel->setPixmap(( mpixmap ));
    }
}

void RadiographWidget::onDisplayPrev()
{
    if( m_current_radiograph > 0 )
    {
        --m_current_radiograph;
        m_ui->DateEdit->setText( m_radiographsModel->record( m_current_radiograph ).field( "Date" ).value().toString() );
        m_ui->DescriptionEdit->setText( m_radiographsModel->record( m_current_radiograph ).field( "Description" ).value().toString() );
        QByteArray data = m_radiographsModel->record( m_current_radiograph ).field( "Radiograph" ).value().toByteArray();
        QPixmap mpixmap = QPixmap();
        if( mpixmap.loadFromData( data ))
            m_ui->imageLabel->setPixmap(( mpixmap ));
    }
}

void RadiographWidget::onUpdateInfo()
{
    if( m_current_radiograph >= 0
            && m_ui->DescriptionEdit->toPlainText() != ""
            && m_ui->DateEdit->toPlainText() != "" )
    {
        m_radiographsModel->setData( m_radiographsModel->index( m_current_radiograph, 1 ), m_ui->DescriptionEdit->toPlainText() );
        m_radiographsModel->setData( m_radiographsModel->index( m_current_radiograph, 2 ), m_ui->DateEdit->toPlainText() );
        m_radiographsModel->submitAll();
        m_radiographsModel->select();
    }
}

void RadiographWidget::displayClear()
{
    QPixmap mpixmap = QPixmap();
    m_ui->imageLabel->setPixmap(( mpixmap ));
    m_ui->DateEdit->setText( "" );
    m_ui->DescriptionEdit->setText( "" );
    m_current_radiograph = -1;
}

void RadiographWidget::onRecordClicked( int id )
{
     m_current_id = id;
}
