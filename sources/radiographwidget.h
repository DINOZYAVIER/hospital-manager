#ifndef RADIOGRAPHWIDGET_H
#define RADIOGRAPHWIDGET_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include "actionstore.h"

namespace Ui {
class RadiographWidget;
}

class RadiographWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RadiographWidget(QWidget *parent = nullptr);
    ~RadiographWidget();

    void setAction();
    void displayClear();
Q_SIGNALS:
    void displayRadiographsSignal( QVariant id );
    void recordClickedSignal( int id );
private Q_SLOTS:
    void onRecordClicked( int id );
    void onAddRadiograph();
    void onRemoveRadiograph();
    void onDisplayRadiograph( QVariant id );
    void onDisplayNext();
    void onDisplayPrev();
    void onUpdateInfo();
private:
    Ui::RadiographWidget *m_ui;
    QSqlDatabase m_db;
    QSqlTableModel* m_radiographsModel;
    int m_current_id;
    int m_current_radiograph;
};

#endif // RADIOGRAPHWIDGET_H
