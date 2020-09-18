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
    void setCurrentID( QVariant id ) { m_current_id = id.toInt(); }
    void displayClear();
    void checkActions();
    void onDisplay( int current_radiograph );
    void openDB();
    void closeDB();
Q_SIGNALS:
    void displayRadiographsSignal();
private Q_SLOTS:
    void onAddRadiograph();
    void onRemoveRadiograph();
    void onDisplayRadiograph();
    void onDisplayNext();
    void onDisplayPrev();
    void onUpdateInfo();
private:
    Ui::RadiographWidget *m_ui;
    QSqlTableModel* m_radiographsModel;
    QVariant m_current_id;
    int m_current_radiograph;
};

#endif // RADIOGRAPHWIDGET_H
