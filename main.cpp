#include "mainwindow.h"
#include "tablewindow.h"
#include "pushbutton.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    TableWindow t(w);
    w->AddTable(&t);
    PushButton b1(w, &t, 0);
    PushButton b2(w, &t, 1);

    w->show();
    return a.exec();
}
