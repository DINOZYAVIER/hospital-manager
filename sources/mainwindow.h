#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QActionGroup>
#include "addpatientdialog.h"
#include "patientrecordwidget.h"
#include "radiographwidget.h"
#include "languagemanager.h"
#include "actionstore.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow( QWidget* parent = nullptr );
    ~MainWindow();

    void loadLanguage( QLocale locale );
    void changeEvent( QEvent* event );
    void loadSettings();
    void saveSettings();
    QSqlDatabase getDB() { return m_db; }

private Q_SLOTS:
    void onAddPatient();
    void onRemovePatient();
    void onDisplayRecords();
    void sortPatients( int index, Qt::SortOrder order );
    void onOpenDB();
    void onCloseDB();
    void languageChange();
    void onAboutQtClicked();

private:
    Ui::MainWindow* m_ui;
    QSqlDatabase    m_db;
    QSqlTableModel* m_patientsModel;
    QActionGroup* m_langGroup;
};

#endif // MAINWINDOW_H
