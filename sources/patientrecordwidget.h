#ifndef PATIENTRECORDWIDGET_H
#define PATIENTRECORDWIDGET_H

#include <QSqlRelationalTableModel>
#include "addrecorddialog.h"
#include "actionstore.h"

namespace Ui {
class PatientRecordWidget;
}

class PatientRecordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PatientRecordWidget(QWidget *parent = nullptr);
    ~PatientRecordWidget();

    void setAction();
    void openDB();
    void closeDB();
Q_SIGNALS:
    void displayRecordsSignal( QVariant id );

private Q_SLOTS:
    void onAddRecord( int id );
    void onRemoveRecord();
    void onDisplayRecords( QVariant id);
    void onDisplayRadiographs();
private:
    Ui::PatientRecordWidget *m_ui;
    QSqlRelationalTableModel *m_recordsModel;
};

#endif // PATIENTRECORDWIDGET_H
