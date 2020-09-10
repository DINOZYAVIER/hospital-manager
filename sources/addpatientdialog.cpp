#include "addpatientdialog.h"
#include "ui_addpatientdialog.h"

AddPatientDialog::AddPatientDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AddPatientDialog)
{
    m_ui->setupUi(this);
    //connect( m_ui->submitButton, &QAction::triggered, parent, &QDialog::reject );
}

AddPatientDialog::~AddPatientDialog()
{
    delete m_ui;
}
