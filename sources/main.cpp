#include "../headers/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    QTranslator* translator = new QTranslator;

    QStringList languages;
    languages << "English" << "Russian";

    QString lang = QInputDialog::getItem(NULL, "Select language", "Language", languages);

    if( lang == "Russian" )
    {
        if( translator->load("/Users/dinozyavier/hospital/resources/russian.qm") )
            qDebug() << "Translation success!" ;
    }

    if( lang != "English" )
        a.installTranslator(translator);





    w->show();
    return a.exec();
}
