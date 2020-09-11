#include "addradiographdialog.h"
#include "ui_addradiographdialog.h"

addRadiographDialog::addRadiographDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::addRadiographDialog)
{
    m_ui->setupUi(this);
}

addRadiographDialog::~addRadiographDialog()
{
    delete m_ui;
}

void addRadiographDialog::onSubmitRecord()
{
    m_data[0] = m_ui->textEditDescription->toPlainText();
    m_data[1] = m_ui->textEditDate->toPlainText();
    m_data[2] = m_ui->textEditPath->toPlainText();
    qDebug() << m_data[0] << m_data[1] << m_data[2];
    this->close();
}
