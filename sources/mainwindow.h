#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow( QWidget* parent = nullptr );
    ~MainWindow();

private Q_SLOTS:
    void onAddPatient();
    void onRemovePatient();
    void sortPatients( int index, Qt::SortOrder order );

private:
    Ui::MainWindow* m_ui;
    QSqlDatabase    m_db;
    QSqlTableModel* m_patientsModel;
    QSqlTableModel* m_recordsModel;
    QSqlTableModel* m_radiographsModel;
};
#endif // MAINWINDOW_H
