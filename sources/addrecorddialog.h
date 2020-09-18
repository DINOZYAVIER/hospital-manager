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

    QString description() { return m_data[0].toString(); }
    QString dateIn() { return m_data[1].toString(); }
    QString dateOut() { return m_data[2].toString(); }
private Q_SLOTS:
    void onTextChanged();

private:
    Ui::AddRecordDialog *m_ui;
    QVariant m_data[3];

};

#endif // ADDRECORDDIALOG_H
