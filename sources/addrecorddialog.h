#ifndef ADDRECORDDIALOG_H
#define ADDRECORDDIALOG_H

#include <QDialog>
#include <QVariant>

namespace Ui {
class AddRecordDialog;
}

class AddRecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecordDialog(QWidget *parent = nullptr);
    ~AddRecordDialog();

    QString description() { return m_data[0]; }
    QString dateIn() { return m_data[1]; }
    QString dateOut() { return m_data[2]; }
private Q_SLOTS:
    void onTextChanged();

private:
    Ui::AddRecordDialog *m_ui;
    QString m_data[3];

};

#endif // ADDRECORDDIALOG_H
