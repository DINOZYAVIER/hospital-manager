#include "patientrecordwidget.h"
#include "ui_patientrecordwidget.h"

PatientRecordWidget::PatientRecordWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::PatientRecordWidget)
{
   m_ui->setupUi(this);
}

PatientRecordWidget::~PatientRecordWidget()
{
    delete m_ui;
}
