#include "precompiled.h"
#include "radiographwidget.h"
#include "ui_radiographwidget.h"

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

    connect( this, &RadiographWidget::displayRadiographsSignal, this, &RadiographWidget::onDisplayRadiograph );
    connect( m_ui->DescriptionEdit, &QTextEdit::textChanged, this, &RadiographWidget::onUpdateInfo );
    connect( m_ui->DateEdit, &QTextEdit::textChanged, this, &RadiographWidget::onUpdateInfo );
    connect( m_ui->addRadiographButton, &QAbstractButton::clicked, this, &RadiographWidget::onAddRadiograph );
}

RadiographWidget::~RadiographWidget()
{
    delete m_ui;
}

void RadiographWidget::onAddRadiograph()
{
    if( m_current_id >= 0 )
    {
        ++m_current_radiograph;
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
    checkActions();
    onDisplay( m_current_radiograph );
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
    }

    if( m_current_radiograph > 0 && m_current_radiograph < m_radiographsModel->rowCount() )
    {
        qDebug() << m_radiographsModel->rowCount();
        qDebug() << "if( m_current_radiograph > 0 && m_current_radiograph < m_radiographsModel->rowCount() )";
        onDisplay( m_current_radiograph - 1 );
        return;
    }

    if( m_radiographsModel->rowCount() == 1 )
    {
        qDebug() << m_radiographsModel->rowCount();
        qDebug() << "if( m_current_radiograph == 0 && m_radiographsModel->rowCount() == 1 )";
        displayClear();
        return;
    }

    if( m_current_radiograph == 0 && m_radiographsModel->rowCount() > 1 )
    {
        qDebug() << m_radiographsModel->rowCount();
        qDebug() << "if( m_current_radiograph == 0 && m_radiographsModel->rowCount() > 1 )";
        onDisplay( m_current_radiograph + 1);
        return;
    }

    if( m_current_radiograph == m_radiographsModel->rowCount() )
    {
        qDebug() << m_radiographsModel->rowCount();
        qDebug() << "if( m_current_radiograph == m_radiographsModel->rowCount() )";
        onDisplay( m_current_radiograph - 1 );
        return;
    }
}

void RadiographWidget::onDisplayRadiograph( QVariant id )
{
    m_current_id = id.toInt();
    m_current_radiograph = 0;
    m_radiographsModel->setFilter( "RecordID='" + id.toString() + "'");


    if( m_radiographsModel->rowCount() > 0)
    {
        onDisplay( m_current_radiograph );
    }
    else
        displayClear();
    checkActions();
}

void RadiographWidget::onDisplayNext()
{
    if( m_current_radiograph >= 0 && m_current_radiograph < m_radiographsModel->rowCount() - 1 )
    {
        ++m_current_radiograph;
        onDisplay( m_current_radiograph );
    }
    checkActions();
}

void RadiographWidget::onDisplayPrev()
{
    if( m_current_radiograph > 0 )
    {
        --m_current_radiograph;
        onDisplay( m_current_radiograph );
    }
    checkActions();
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

void RadiographWidget::setAction()
{
    connect( ActionStore::action( aAddRadiograph ), &QAction::triggered, this, &RadiographWidget::onAddRadiograph );
    connect( ActionStore::action( aRemoveRadiograph ), &QAction::triggered, this, &RadiographWidget::onRemoveRadiograph );
    connect( ActionStore::action( aNextRadiograph ), &QAction::triggered, this, &RadiographWidget::onDisplayNext );
    connect( ActionStore::action( aPrevRadiograph ), &QAction::triggered, this, &RadiographWidget::onDisplayPrev );
}

void RadiographWidget::checkActions()
{
    if( m_current_radiograph == 0 )
        ActionStore::action( aPrevRadiograph )->setEnabled( false );
    else
        ActionStore::action( aPrevRadiograph )->setEnabled( true );
    if( m_current_radiograph ==  m_radiographsModel->rowCount() - 1 )
        ActionStore::action( aNextRadiograph )->setEnabled( false );
    else
        ActionStore::action( aNextRadiograph )->setEnabled( true );
}

void RadiographWidget::onDisplay( int current_radiograph)
{
    m_ui->DateEdit->setText( m_radiographsModel->record( current_radiograph ).field( "Date" ).value().toString() );
    m_ui->DescriptionEdit->setText( m_radiographsModel->record( current_radiograph ).field( "Description" ).value().toString() );
    QByteArray data = m_radiographsModel->record( current_radiograph ).field( "Radiograph" ).value().toByteArray();
    QPixmap mpixmap = QPixmap();
    if( mpixmap.loadFromData( data ))
        m_ui->imageLabel->setPixmap(( mpixmap ));
    else
        m_ui->imageLabel->setPixmap(( QPixmap() ));
}

void RadiographWidget::openDB()
{
    m_radiographsModel->setTable( "Radiographs" );
    m_radiographsModel->select();
}

void RadiographWidget::closeDB()
{
    m_radiographsModel->clear();
}
