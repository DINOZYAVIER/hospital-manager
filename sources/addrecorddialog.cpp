#include "precompiled.h"
#include "addrecorddialog.h"
#include "ui_addrecorddialog.h"

AddRecordDialog::AddRecordDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AddRecordDialog)
{
    m_ui->setupUi(this);
    connect( m_ui->submitButton, &QAbstractButton::clicked, this, &QDialog::accept );
    connect( m_ui->cancelButton, &QAbstractButton::clicked, this, &QDialog::close );

    connect( m_ui->dateEditDateIn, &QDateEdit::dateChanged, this, &AddRecordDialog::onTextChanged );
    connect( m_ui->dateEditDateOut, &QDateEdit::dateChanged, this, &AddRecordDialog::onTextChanged );
    connect( m_ui->textEditDescription, &QTextEdit::textChanged, this, &AddRecordDialog::onTextChanged );
}

AddRecordDialog::~AddRecordDialog()
{
    delete m_ui;
}

void AddRecordDialog::onTextChanged()
{
    m_data[0] = m_ui->textEditDescription->toPlainText();
    m_data[1] = m_ui->dateEditDateIn->text();
    m_data[2] = m_ui->dateEditDateOut->text();
}

