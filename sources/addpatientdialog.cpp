#include "addpatientdialog.h"
#include "ui_addpatientdialog.h"

AddPatientDialog::AddPatientDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AddPatientDialog)
{
    m_ui->setupUi(this);
    //connect( m_ui->submitButton, &QAction::triggered, this, &QDialog::close);
}

AddPatientDialog::~AddPatientDialog()
{
    delete m_ui;
}
