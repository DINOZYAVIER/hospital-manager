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
    void setCurrentID( QVariant id ) { m_current_id = id; }
    void openDB();
    void closeDB();
Q_SIGNALS:
    void displayRecordsSignal();

private Q_SLOTS:
    void onAddRecord();
    void onRemoveRecord();
    void onDisplayRecords();
    void onDisplayRadiographs();
private:
    Ui::PatientRecordWidget *m_ui;
    QSqlRelationalTableModel *m_recordsModel;
    QVariant m_current_id;
};

#endif // PATIENTRECORDWIDGET_H
