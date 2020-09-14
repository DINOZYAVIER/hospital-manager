#include "addradiographdialog.h"
#include "ui_addradiographdialog.h"

addRadiographDialog::addRadiographDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::addRadiographDialog)
{
    m_ui->setupUi(this);

    connect( m_ui->AddPathButton, &QAbstractButton::clicked, this, &addRadiographDialog::onAddPath );
    connect( m_ui->submitButton, &QAbstractButton::clicked, this, &addRadiographDialog::onSubmitRecord );
    connect( m_ui->cancelButton, &QAbstractButton::clicked, this, &QDialog::close );
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

    QFile file( m_data[2].toString() );
    if ( !file.open( QIODevice::ReadOnly ) )
        return;
    QByteArray inByteArray = file.readAll();
    m_data[2] = inByteArray;

    this->close();
}

void addRadiographDialog::onAddPath()
{
    QString fileName = QFileDialog::getOpenFileName( this,
        tr( "Open Image" ), QCoreApplication::applicationDirPath(), tr( "Image Files (*.png *.jpg *.bmp)" ) );
    m_ui->textEditPath->setText( fileName );
}
