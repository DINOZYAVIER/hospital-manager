#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTranslator>
#include <QLocale>
#include <QActionGroup>
#include "addpatientdialog.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow( QWidget* parent = nullptr );
    ~MainWindow();

    void loadLanguage( QLocale locale );
    void changeEvent( QEvent* event );

private Q_SLOTS:
    void onAddPatient();
    void onRemovePatient();
    void onDisplayRecords();
    void onAddRecord();
    void onRemoveRecord();
    void onDisplayRadiographs();
    void onAddRadiograph();
    void onRemoveRadiograph();
    void onDisplayEverything();
    void sortPatients( int index, Qt::SortOrder order );
    void languageChange();

private:
    Ui::MainWindow* m_ui;
    QSqlDatabase    m_db;
    QSqlTableModel* m_patientsModel;
    QSqlTableModel* m_recordsModel;
    QSqlTableModel* m_radiographsModel;
    QTranslator m_translator;
    QLocale m_curLang;
    QActionGroup* m_langGroup;
};

void SwitchTranslator( QTranslator& translator, const QString& language );
#endif // MAINWINDOW_H
