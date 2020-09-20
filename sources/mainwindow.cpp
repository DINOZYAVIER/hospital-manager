#include "precompiled.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

LanguageManager &lm = LanguageManager::instance();

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
    , m_ui( new Ui::MainWindow )
{
    loadSettings();
    m_db = QSqlDatabase::addDatabase( "QSQLITE" );
    m_db.setDatabaseName( QCoreApplication::applicationDirPath() + "/HospitalDB.db" );
    if( m_db.open() )
        m_db.exec( "PRAGMA foreign_keys = ON" );
    m_ui->setupUi( this );

    ActionStore::addAction( aAddPatient, m_ui->aAddPatient );
    ActionStore::addAction( aRemovePatient, m_ui->aRemovePatient) ;
    ActionStore::addAction( aAddRecord, m_ui->aAddRecord );
    ActionStore::addAction( aRemoveRecord, m_ui->aRemoveRecord );
    ActionStore::addAction( aAddRadiograph, m_ui->aAddRadiograph );
    ActionStore::addAction( aRemoveRadiograph, m_ui->aRemoveRadiograph );
    ActionStore::addAction( aNextRadiograph, m_ui->aNextRadiograph );
    ActionStore::addAction( aPrevRadiograph, m_ui->aPrevRadiograph );

    ActionStore::action( aAddRecord )->setEnabled( false );
    ActionStore::action( aRemoveRecord )->setEnabled( false );
    ActionStore::action( aAddRadiograph )->setEnabled( false );
    ActionStore::action( aRemoveRadiograph )->setEnabled( false );
    ActionStore::action( aNextRadiograph )->setEnabled( false );
    ActionStore::action( aPrevRadiograph )->setEnabled( false );


    m_patientsModel = new QSqlTableModel( this );
    m_patientsModel->setTable( "Patients" );
    m_patientsModel->select();
    m_ui->patientTable->setModel( m_patientsModel );

    connect( m_ui->aOpenDB, &QAction::triggered, this, &MainWindow::onOpenDB );
    connect( m_ui->aCloseDB, &QAction::triggered, this, &MainWindow::onCloseDB );
    connect( ActionStore::action( aAddPatient ), &QAction::triggered, this, &MainWindow::onAddPatient );
    connect( ActionStore::action( aRemovePatient ), &QAction::triggered, this, &MainWindow::onRemovePatient );
    connect( m_ui->patientTable, &QTableView::clicked, this, &MainWindow::onDisplayRecords );
    connect( m_ui->aAbout, &QAction::triggered, this, &MainWindow::onAboutClicked );
    connect( m_ui->aAboutQt, &QAction::triggered, this, &MainWindow::onAboutQtClicked );


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

    m_ui->recordsWidget->setAction();
    //m_ui->recordsWidget->setCurrentID( 0 );
    emit m_ui->recordsWidget->displayRecordsSignal();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete m_ui;
    m_db.close();
}

void MainWindow::onAddPatient()
{
    AddPatientDialog dialogWnd;
    dialogWnd.setWindowTitle( "Add patient" );
    dialogWnd.setModal(true);
    if( dialogWnd.exec() == QDialog::Accepted )
    {
        QSqlRecord record( m_patientsModel->record() );
        record.setValue( 0, QVariant() );
        record.setValue( 1, dialogWnd.name() );
        record.setValue( 2, dialogWnd.date() );
        record.setValue( 3, dialogWnd.address() );
        m_patientsModel->insertRecord( -1, record );
        m_patientsModel->submitAll();
        m_patientsModel->select();
        qDebug() << "Added patient with ID:" << m_patientsModel->record( m_patientsModel->rowCount() - 1 ).field( 0 ).value().toInt();
    }
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
    ActionStore::action( aAddRecord )->setEnabled( true );
    ActionStore::action( aRemoveRecord )->setEnabled( false );
    ActionStore::action( aAddRadiograph )->setEnabled( false );
    ActionStore::action( aRemoveRadiograph )->setEnabled( false );
    ActionStore::action( aNextRadiograph )->setEnabled( false );
    ActionStore::action( aPrevRadiograph )->setEnabled( false );

    auto currentIndex = m_ui->patientTable->selectionModel()->currentIndex();
    QVariant id = m_patientsModel->record( currentIndex.row() ).field( 0 ).value().toInt();
    if( currentIndex.isValid() )
    {
        m_ui->recordsWidget->setCurrentID( id );
        emit m_ui->recordsWidget->displayRecordsSignal();
    }
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
    lm.loadLanguage( lang );
    settings.endGroup();
}
void MainWindow::saveSettings()
{
    //here we save settings
    QSettings settings( QStandardPaths::displayName (QStandardPaths::AppDataLocation) + "/hospital.ini",
                        QSettings::IniFormat);
    settings.beginGroup( "MainWindow" );
    settings.setValue( "language", lm.CurLang() );
    settings.endGroup();
}

void MainWindow::onOpenDB()
{
    QString fileName = QFileDialog::getOpenFileName( this,
        tr( "Open DB" ), QCoreApplication::applicationDirPath(), tr( "*db" ) );
    m_db.setDatabaseName( fileName );
    if( m_db.open() )
    {
        m_db.exec( "PRAGMA foreign_keys = ON" );
        m_patientsModel->setTable( "Patients" );
        m_patientsModel->select();
        m_ui->patientTable->setModel( m_patientsModel );
        ActionStore::action( aAddPatient )->setEnabled( true );
        ActionStore::action( aRemovePatient )->setEnabled( true );
        m_ui->recordsWidget->openDB();
    }
    else
        qDebug() << "DB not found";
}

void MainWindow::onCloseDB()
{
     m_db.close();

     ActionStore::action( aAddPatient )->setEnabled( false );
     ActionStore::action( aRemovePatient )->setEnabled( false );
     ActionStore::action( aAddRecord )->setEnabled( false );
     ActionStore::action( aRemoveRecord )->setEnabled( false );
     ActionStore::action( aAddRadiograph )->setEnabled( false );
     ActionStore::action( aRemoveRadiograph )->setEnabled( false );
     ActionStore::action( aNextRadiograph )->setEnabled( false );
     ActionStore::action( aPrevRadiograph )->setEnabled( false );
     m_patientsModel->clear();
     m_ui->recordsWidget->closeDB();
}

void MainWindow::onAboutClicked()
{
    QMessageBox::about( this, "About the program",
                              "Hospital Management Application \nTest assignment by Arthur Konovalov for NIX Solutions.");
}

void MainWindow::onAboutQtClicked()
{
    QMessageBox::aboutQt( this, "About Qt" );
}
