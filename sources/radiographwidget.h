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
#include <addradiographdialog.h>

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
    void nextRadiographSignal();
    void prevRadiographSignal();
private Q_SLOTS:
    void onConstruct( QSqlDatabase db );
    void onAddRadiograph( int id );
    void onRemoveRadiograph();
    void onDisplayRadiograph( QVariant id );
    void onDisplayNext();
    void onDisplayPrev();
private:
    Ui::RadiographWidget *m_ui;
    QSqlDatabase m_db;
    QSqlTableModel* m_radiographsModel;
    int m_current_id;
};

#endif // RADIOGRAPHWIDGET_H
