#include "precompiled.h"
#include "addpatientdialog.h"
#include "ui_addpatientdialog.h"

AddPatientDialog::AddPatientDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AddPatientDialog)
{
    m_ui->setupUi(this);
    connect( m_ui->submitButton, &QAbstractButton::clicked, this, &QDialog::accept );
    connect( m_ui->cancelButton, &QAbstractButton::clicked, this, &QDialog::close );

    connect( m_ui->lineEditAddress, &QLineEdit::textChanged, this, &AddPatientDialog::onTextChanged );
    connect( m_ui->dateEditBirthday, &QDateEdit::dateChanged, this, &AddPatientDialog::onTextChanged );
    connect( m_ui->lineEditName, &QLineEdit::textChanged, this, &AddPatientDialog::onTextChanged );
}

AddPatientDialog::~AddPatientDialog()
{
    delete m_ui;
}

void AddPatientDialog::onTextChanged()
{
    m_data[0] = m_ui->lineEditName->text();
    m_data[1] = m_ui->dateEditBirthday->text();
    m_data[2] = m_ui->lineEditAddress->text();
}


