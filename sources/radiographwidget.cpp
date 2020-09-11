#include "radiographwidget.h"
#include "ui_radiographwidget.h"

RadiographWidget::RadiographWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::RadiographWidget)
{
    m_ui->setupUi(this);

    connect( this, &RadiographWidget::constructSignal, this, &RadiographWidget::onConstruct );
}

RadiographWidget::~RadiographWidget()
{
    delete m_ui;
}

void RadiographWidget::onConstruct( QSqlDatabase db )
{
    m_db = db;
}

void RadiographWidget::onAddRadiograph( int id )
{

}

void RadiographWidget::onRemoveRadiograph( )
{

}

void RadiographWidget::onDisplayRadiographs( QVariant id )
{

}

