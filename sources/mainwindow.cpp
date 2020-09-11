#include "precompiled.h"
#include "mainwindow.h"
#include "languagemanager.h"
#include "ui_mainwindow.h"

LanguageManager &lm = LanguageManager::get_instance();

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow(parent)
    , m_ui( new Ui::MainWindow )
{
    loadSettings();
    m_ui->setupUi( this );
    m_db = QSqlDatabase::addDatabase( "QSQLITE" );
    m_db.setDatabaseName( QCoreApplication::applicationDirPath() + "/HospitalDB.db" );
    qDebug() << QCoreApplication::applicationDirPath();
    m_db.open();
    m_db.exec( "PRAGMA foreign_keys = ON" );

    m_patientsModel = new QSqlTableModel( this );
    m_patientsModel->setTable( "Patients" );
    m_patientsModel->select();
    m_ui->patientTable->setModel( m_patientsModel );

    m_recordsModel = new QSqlTableModel( this );
    m_recordsModel->setTable( "ClinicalRecords" );
    m_recordsModel->select();
    m_ui->recordTable->setModel( m_recordsModel );

    m_radiographsModel = new QSqlTableModel( this );
    m_radiographsModel->setTable( "Radiographs" );
    m_radiographsModel->select();
    m_ui->radiographTable->setModel( m_radiographsModel );

    connect( m_ui->aAddPatient, &QAction::triggered, this, &MainWindow::onAddPatient );
    connect( m_ui->aRemovePatient, &QAction::triggered, this, &MainWindow::onRemovePatient );

    connect( m_ui->aDisplayRecords, &QAction::triggered, this, &MainWindow::onDisplayRecords );
    connect( m_ui->aAddRecord, &QAction::triggered, this, &MainWindow::onAddRecord );
    connect( m_ui->aRemoveRecord, &QAction::triggered, this, &MainWindow::onRemoveRecord );

    connect( m_ui->aDisplayRadiographs, &QAction::triggered, this, &MainWindow::onDisplayRadiographs );
    connect( m_ui->aAddRadiograph, &QAction::triggered, this, &MainWindow::onAddRadiograph );
    connect( m_ui->aRemoveRadiograph, &QAction::triggered, this, &MainWindow::onRemoveRadiograph );

    connect( m_ui->aDisplayEverything, &QAction::triggered, this, &MainWindow::onDisplayEverything );

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

    //m_ui->aDisplayRecords->setVisible(false);
    //m_ui->aDisplayRadiographs->setVisible(false);
    m_ui->aDisplayEverything->setVisible(false);
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

    PatientRecordWidget PatRecWidget;
    PatRecWidget.show();

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
        m_recordsModel->select();
        m_radiographsModel->select();
        qDebug() << "Removed patient with ID:" << id;
    }
}

void MainWindow::onDisplayRecords()
{
    m_ui->recordTable->hideColumn(4);

    auto currentIndex = m_ui->patientTable->selectionModel()->currentIndex();

    if( currentIndex.isValid() )
    {
        QVariant id = m_patientsModel->record( currentIndex.row() ).field( 0 ).value().toInt();
        qDebug() << id;
        m_recordsModel->setFilter("PatientID='" + id.toString() + "'");
    }
}

void MainWindow::onAddRecord()
{
    AddRecordDialog dial;
    dial.exec();
    QVariant* data = dial.getData();

    auto currentIndex = m_ui->patientTable->selectionModel()->currentIndex();
    int id = m_patientsModel->record( currentIndex.row() ).field( 0 ).value().toInt();

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

void MainWindow::onRemoveRecord()
{
    auto currentIndex = m_ui->recordTable->selectionModel()->currentIndex();
    if( currentIndex.isValid() )
    {
        int id = m_recordsModel->record( currentIndex.row() ).field( 0 ).value().toInt();
        m_recordsModel->removeRow( currentIndex.row() );
        m_recordsModel->submitAll();
        m_recordsModel->select();
        m_radiographsModel->select();
        qDebug() << "Removed record with ID:" << id;
    }
}

void MainWindow::onDisplayRadiographs()
{
    m_ui->radiographTable->hideColumn(4);
    auto currentIndex = m_ui->recordTable->selectionModel()->currentIndex();

    if( currentIndex.isValid() )
    {
        QVariant id = m_recordsModel->record( currentIndex.row() ).field( 0 ).value().toInt();
        m_radiographsModel->setFilter("RecordID='" + id.toString() + "'");
    }
}

void MainWindow::onAddRadiograph()
{
    auto currentIndex = m_ui->recordTable->selectionModel()->currentIndex();
    int id = m_recordsModel->record( currentIndex.row() ).field( 0 ).value().toInt();

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

void MainWindow::onRemoveRadiograph()
{
    auto currentIndex = m_ui->radiographTable->selectionModel()->currentIndex();
    if( currentIndex.isValid() )
    {
        int id = m_radiographsModel->record( currentIndex.row() ).field( 0 ).value().toInt();
        m_radiographsModel->removeRow( currentIndex.row() );
        m_radiographsModel->submitAll();
        m_radiographsModel->select();
        qDebug() << "Removed radiograph with ID:" << id;
    }
}

void MainWindow::onDisplayEverything()
{
    int rows = m_recordsModel->rowCount();
    for( int i = 0; i < rows; ++i)
        if( m_ui->recordTable->isRowHidden( i ) )
            m_ui->recordTable->showRow(i);

    rows = m_radiographsModel->rowCount();
    for( int i = 0; i < rows; ++i)
        if( m_ui->radiographTable->isRowHidden( i ) )
            m_ui->radiographTable->showRow(i);
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
    //QSettings settings( QSettings::IniFormat, QSettings::UserScope,"NIX Solutions", "Hospital" );
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


