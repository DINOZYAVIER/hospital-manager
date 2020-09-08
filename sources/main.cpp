#include "precompiled.h"
#include "mainwindow.h"

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    QTranslator translator;
    QStringList languages { "English" , "Russian" };
    QString lang = QInputDialog::getItem( NULL, "Select language", "Language", languages );
    if( lang == "Russian" )
    {
        if( translator.load(":/translations/hospital_ru.qm") )
            qDebug() << "Translation success!" ;
    }
    app.installTranslator( &translator );

    MainWindow mainWin;
    mainWin.show();

    return app.exec();
}
