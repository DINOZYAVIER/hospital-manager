#include "addpatientdialog.h"
#include "ui_addpatientdialog.h"
#include "precompiled.h"

AddPatientDialog::AddPatientDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AddPatientDialog)
{
    m_ui->setupUi(this);
    connect( m_ui->submitButton, &QAbstractButton::clicked, this, &AddPatientDialog::onSubmit );
    connect( m_ui->cancelButton, &QAbstractButton::clicked, this, &QDialog::close );

}

AddPatientDialog::~AddPatientDialog()
{
    delete m_ui;
}

void AddPatientDialog::onSubmit()
{
    m_data[0] = m_ui->textEditName->toPlainText();
    m_data[1] = m_ui->textEditBirthday->toPlainText();
    m_data[2] = m_ui->textEditAddress->toPlainText();
    qDebug() << m_data[0] << m_data[1] << m_data[2];
    this->close();
}


