#ifndef ADDPATIENTDIALOG_H
#define ADDPATIENTDIALOG_H

#include <QDialog>
#include <QAction>

namespace Ui {
class AddPatientDialog;
}

class AddPatientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPatientDialog(QWidget *parent = nullptr);
    ~AddPatientDialog();

private:
    Ui::AddPatientDialog *m_ui;
};

#endif // ADDPATIENTDIALOG_H
