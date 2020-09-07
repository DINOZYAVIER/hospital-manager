#include "../headers/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    QTranslator myappTranslator;
       myappTranslator.load(QLocale(), QLatin1String("myapp"), QLatin1String("_"), QLatin1String(":/i18n"));
       a.installTranslator(&myappTranslator);

    w->show();
    return a.exec();
}
