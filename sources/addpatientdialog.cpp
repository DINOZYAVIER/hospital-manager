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

    connect( m_ui->textEditAddress, &QTextEdit::textChanged, this, &AddPatientDialog::onTextChanged );
    connect( m_ui->textEditBirthday, &QTextEdit::textChanged, this, &AddPatientDialog::onTextChanged );
    connect( m_ui->textEditName, &QTextEdit::textChanged, this, &AddPatientDialog::onTextChanged );
}

AddPatientDialog::~AddPatientDialog()
{
    delete m_ui;
}

void AddPatientDialog::onTextChanged()
{
    m_data[0] = m_ui->textEditName->toPlainText();
    m_data[1] = m_ui->textEditBirthday->toPlainText();
    m_data[2] = m_ui->textEditAddress->toPlainText();
}


