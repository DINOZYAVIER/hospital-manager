#ifndef PATIENTRECORDWIDGET_H
#define PATIENTRECORDWIDGET_H

#include <QWidget>

namespace Ui {
class PatientRecordWidget;
}

class PatientRecordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PatientRecordWidget(QWidget *parent = nullptr);
    ~PatientRecordWidget();

private:
    Ui::PatientRecordWidget *m_ui;
};

#endif // PATIENTRECORDWIDGET_H
