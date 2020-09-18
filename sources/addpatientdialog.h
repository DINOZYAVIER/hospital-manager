#ifndef ADDPATIENTDIALOG_H
#define ADDPATIENTDIALOG_H

#include <QDialog>
#include <QVariant>

namespace Ui {
class AddPatientDialog;
}

class AddPatientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPatientDialog(QWidget *parent = nullptr);
    ~AddPatientDialog();

    QString name() { return m_data[0].toString(); }
    QString date() { return m_data[1].toString(); }
    QString address() { return m_data[2].toString(); }
private Q_SLOTS:
    void onTextChanged();

private:
    Ui::AddPatientDialog *m_ui;
    QVariant m_data[3];
};

#endif // ADDPATIENTDIALOG_H
