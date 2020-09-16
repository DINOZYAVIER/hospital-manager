#include "precompiled.h"
#include "addrecorddialog.h"
#include "ui_addrecorddialog.h"

AddRecordDialog::AddRecordDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AddRecordDialog)
{
    m_ui->setupUi(this);
    connect( m_ui->submitButton, &QAbstractButton::clicked, this, &AddRecordDialog::onSubmitRecord );
    connect( m_ui->cancelButton, &QAbstractButton::clicked, this, &QDialog::close );
}

AddRecordDialog::~AddRecordDialog()
{
    delete m_ui;
}

void AddRecordDialog::onSubmitRecord()
{
    m_data[0] = m_ui->textEditDescription->toPlainText();
    m_data[1] = m_ui->textEditDateIn->toPlainText();
    m_data[2] = m_ui->textEditDateOut->toPlainText();
    qDebug() << m_data[0] << m_data[1] << m_data[2];
    this->close();
}

