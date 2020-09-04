#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "tablewindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void AddTable(TableWindow *t);

private slots:
    void handleAddButton();
    void handleDeleteButton();

private:
    Ui::MainWindow *ui;
    TableWindow *t;
};
#endif // MAINWINDOW_H
