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

    QVariant* getData() { return m_data; }

private Q_SLOTS:
    void onSubmitRecord();

private:
    Ui::AddRecordDialog *m_ui;
    QVariant m_data[3];

};

#endif // ADDRECORDDIALOG_H
