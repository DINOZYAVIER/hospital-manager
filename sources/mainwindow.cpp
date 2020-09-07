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

void MainWindow::handleAddButton()
{
    t->AddPatient();
    qDebug() << "hello there";
}

void MainWindow::handleDeleteButton()
{
    t->DeletePatient();
    qDebug() << "hello there everyone";
}

void MainWindow::AddTable(TableWindow *t)
{
    this->t = t;
}


