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

    QVariant* getData() { return m_data; }

private Q_SLOTS:
    void onTextChanged();

private:
    Ui::AddPatientDialog *m_ui;
    QVariant m_data[3];
};

#endif // ADDPATIENTDIALOG_H
