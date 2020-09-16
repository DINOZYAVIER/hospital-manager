#include "precompiled.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

LanguageManager &lm = LanguageManager::get_instance();

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
    , m_ui( new Ui::MainWindow )
{
    loadSettings();
    m_ui->setupUi( this );

    ActionStore::addAction( aAddPatient, m_ui->aAddPatient );
    ActionStore::addAction( aRemovePatient, m_ui->aRemovePatient) ;
    ActionStore::addAction( aAddRecord, m_ui->aAddRecord );
    ActionStore::addAction( aRemoveRecord, m_ui->aRemoveRecord );
    ActionStore::addAction( aAddRadiograph, m_ui->aRemoveRadiograph );
    ActionStore::addAction( aRemoveRadiograph, m_ui->aRemoveRadiograph );
    ActionStore::addAction( aNextRadiograph, m_ui->aNextRadiograph );
    ActionStore::addAction( aPrevRadiograph, m_ui->aPrevRadiograph );

    m_db = QSqlDatabase::addDatabase( "QSQLITE" );
    m_db.setDatabaseName( QCoreApplication::applicationDirPath() + "/HospitalDB.db" );
    qDebug() << QCoreApplication::applicationDirPath();
    m_db.open();
    m_db.exec( "PRAGMA foreign_keys = ON" );

    m_patientsModel = new QSqlTableModel( this );
    m_patientsModel->setTable( "Patients" );
    m_patientsModel->select();
    m_ui->patientTable->setModel( m_patientsModel );

    connect( ActionStore::action( aAddPatient ), &QAction::triggered, this, &MainWindow::onAddPatient );
    connect( ActionStore::action( aRemovePatient ), &QAction::triggered, this, &MainWindow::onRemovePatient );
    connect( m_ui->patientTable, &QTableView::clicked, this, &MainWindow::onDisplayRecords );

    //db sort
    auto* header = m_ui->patientTable->horizontalHeader();
    connect( header, &QHeaderView::sortIndicatorChanged, this, &MainWindow::sortPatients );

    //translation
    m_langGroup = new QActionGroup( this );
    m_langGroup->addAction( m_ui->aEnglish );
    m_langGroup->addAction( m_ui->aRussian );
    m_langGroup->setExclusive( true );
    m_ui->aEnglish->setCheckable( true );
    m_ui->aRussian->setCheckable( true );
    connect( m_langGroup, &QActionGroup::triggered, this, &MainWindow::languageChange );

    emit m_ui->recordsWidget->displayRecordsSignal( 0 );
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete m_ui;
    m_db.close();
}

void MainWindow::onAddPatient()
{
    AddPatientDialog dial;
    dial.setModal(true);
    dial.exec();

    QVariant* data = dial.getData();
    qDebug() << data[0] << data[1] << data[2];

    QSqlRecord record( m_patientsModel->record() );
    record.setValue( 0, QVariant() );
    record.setValue( 1, data[0] );
    record.setValue( 2, data[1] );
    record.setValue( 3, data[2] );
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

void MainWindow::onDisplayRecords()
{
    auto currentIndex = m_ui->patientTable->selectionModel()->currentIndex();
    QVariant id = m_patientsModel->record( currentIndex.row() ).field( 0 ).value().toInt();
    if( currentIndex.isValid() )
        emit m_ui->recordsWidget->displayRecordsSignal( id );
}

void MainWindow::sortPatients( int index, Qt::SortOrder order )
{
    qDebug() << "Sort " << index << order;
    m_patientsModel->sort( index, order );
}

void MainWindow::languageChange()
{
    lm.loadLanguage( m_langGroup->checkedAction()->toolTip() );
}

void MainWindow::changeEvent( QEvent* event )
{
    if( 0 != event )
    {
        switch( event->type() )
        {
            // this event is send if a translator is loaded
            case QEvent::LanguageChange:
                m_ui->retranslateUi(this);
                break;
        }
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::loadSettings()
{
    //here we load settings
    QSettings settings( QStandardPaths::displayName (QStandardPaths::AppDataLocation) + "/hospital.ini",
                        QSettings::IniFormat );
    settings.beginGroup( "MainWindow" );
    QString lang = settings.value( "language", "en" ).toString();
    lm.loadLanguage(lang);
    settings.endGroup();
}
void MainWindow::saveSettings()
{
    //here we save settings
    QSettings settings( QStandardPaths::displayName (QStandardPaths::AppDataLocation) + "/hospital.ini",
                        QSettings::IniFormat);
    settings.beginGroup( "MainWindow" );
    settings.setValue( "language", lm.getCurLang() );
    settings.endGroup();
}


