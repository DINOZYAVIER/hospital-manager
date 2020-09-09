#include "precompiled.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow(parent)
    , m_ui( new Ui::MainWindow )
{
    m_ui->setupUi( this );
    m_db = QSqlDatabase::addDatabase( "QSQLITE" );
    m_db.setDatabaseName( QCoreApplication::applicationDirPath() + "/HospitalDB.db" );
    qDebug() << QCoreApplication::applicationDirPath();
    m_db.open();

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

    //add and remove patient buttons
    connect( m_ui->aAddPatient, &QAction::triggered, this, &MainWindow::onAddPatient );
    connect( m_ui->aRemovePatient, &QAction::triggered, this, &MainWindow::onRemovePatient );

    //db sort
    auto* header = m_ui->patientTable->horizontalHeader();
    connect( header, &QHeaderView::sortIndicatorChanged, this, &MainWindow::sortPatients );

    //translation buttons
    connect( m_ui->aEnglish, &QAction::triggered, this, &MainWindow::languageChangeEnglish );
    connect( m_ui->aRussian, &QAction::triggered, this, &MainWindow::languageChangeRussian );
}

MainWindow::~MainWindow()
{
    delete m_ui;
    m_db.close();
}

void MainWindow::onAddPatient()
{
    QSqlRecord record( m_patientsModel->record() );
    record.setValue( 0, QVariant() );
    record.setValue( 1, "" );
    record.setValue( 2, QVariant( "01.01.1980" ) );
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

void MainWindow::sortPatients( int index, Qt::SortOrder order )
{
    qDebug() << "Sort " << index << order;
    m_patientsModel->sort( index, order );
}

void MainWindow::languageChangeEnglish()
{
    qDebug() << "English triggered";
    QLocale locale = QLocale( QLocale::English );
    loadLanguage( locale );
}

void MainWindow::languageChangeRussian()
{
    qDebug() << "Russian triggered";
    QLocale locale = QLocale( QLocale::Russian );
    loadLanguage( locale );
}

void SwitchTranslator( QTranslator& translator, const QString& language )
{
    // remove the old translator
     qApp->removeTranslator( &translator );

     // load the new translator
     if( translator.load( ":/translations/hospital_" + language + ".qm") )
         qApp->installTranslator(&translator);
}

void MainWindow::loadLanguage( QLocale locale )
{
    if(m_curLang != locale)
    {
      m_curLang = locale;
      QLocale::setDefault(locale);
      QString languageName = QLocale::languageToString( locale.language() );
      //qDebug() << QString("TranslationExample_%1.qm").arg(language);

      QString defaultLocale = locale.name(); // e.g. "de_DE"
      qDebug() << defaultLocale;

       defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"
       qDebug() << defaultLocale;

      SwitchTranslator(m_translator, defaultLocale);
      //switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
      //ui.statusBar->showMessage(tr("Current Language changed to %1").arg(languageName));
    }
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

            // this event is send, if the system, language changes
            case QEvent::LocaleChange:
                QString locale = QLocale::system().name();
                locale.truncate(locale.lastIndexOf('_'));
                loadLanguage(locale);
                break;
        }
    }
    QMainWindow::changeEvent(event);
}


