#include "precompiled.h"
#include "mainwindow.h"

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
    MainWindow mainWin;
    mainWin.show();

    return app.exec();
}
