#ifndef RADIOGRAPHWIDGET_H
#define RADIOGRAPHWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlField>

namespace Ui {
class RadiographWidget;
}

class RadiographWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RadiographWidget(QWidget *parent = nullptr);
    ~RadiographWidget();
Q_SIGNALS:
    void constructSignal( QSqlDatabase db );
    void addRadiographSignal( int id );
    void removeRadiographSignal();
    void displayRadiographsSignal( QVariant id );
private Q_SLOTS:
    void onConstruct( QSqlDatabase db );
    void onAddRadiograph( int id );
    void onRemoveRadiograph();
    void onDisplayRadiographs( QVariant id );
private:
    Ui::RadiographWidget *m_ui;
    QSqlDatabase m_db;
    QSqlTableModel* m_radiographsModel;
};

#endif // RADIOGRAPHWIDGET_H
