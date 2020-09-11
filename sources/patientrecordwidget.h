#ifndef PATIENTRECORDWIDGET_H
#define PATIENTRECORDWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <precompiled.h>
#include "mainwindow.h"
#include "addrecorddialog.h"

namespace Ui {
class PatientRecordWidget;
}

class PatientRecordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PatientRecordWidget(QWidget *parent = nullptr);
    ~PatientRecordWidget();
Q_SIGNALS:
    void constructSignal( QSqlDatabase db );
    void addRecordSignal( int id );
    void removeRecordSignal();
    void displayRecordsSignal( QVariant id);
private Q_SLOTS:
    void onConstruct( QSqlDatabase db );
    void onAddRecord( int id );
    void onRemoveRecord();
    void onDisplayRecords( QVariant id);

private:
    Ui::PatientRecordWidget *m_ui;
    QSqlDatabase m_db;
    QSqlTableModel* m_recordsModel;
};

#endif // PATIENTRECORDWIDGET_H
