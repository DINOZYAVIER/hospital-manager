#ifndef ADDRADIOGRAPHDIALOG_H
#define ADDRADIOGRAPHDIALOG_H

#include <QDialog>
#include <QVariant>
#include <QDebug>

namespace Ui {
class addRadiographDialog;
}

class addRadiographDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addRadiographDialog(QWidget *parent = nullptr);
    ~addRadiographDialog();

    QVariant* getData() { return m_data; }
    void onSubmitRecord();
private:
    Ui::addRadiographDialog *m_ui;
    QVariant m_data[3];
};

#endif // ADDRADIOGRAPHDIALOG_H
