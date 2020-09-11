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
    void addRecordSignal( int id );
    void removeRecordSignal();
    void constructSignal( QSqlDatabase db );
private Q_SLOTS:
    void onAddRecord( int id );
    void onRemoveRecord();
    void onConstruct( QSqlDatabase db );
private:
    Ui::PatientRecordWidget *m_ui;
    QSqlDatabase m_db;
    QSqlTableModel* m_recordsModel;
};

#endif // PATIENTRECORDWIDGET_H
