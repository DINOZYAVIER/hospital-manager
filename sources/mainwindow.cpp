#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddTable(TableWindow *t)
{
    this->t = t;
}



void MainWindow::on_actionAdd_triggered()
{
    t->AddPatient();
    qDebug() << "hello there";
}

void MainWindow::on_actionRemove_triggered()
{
    t->DeletePatient();
}
