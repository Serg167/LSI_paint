#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSplashScreen splash(QPixmap(":/splash.gif"));
    splash.show();
    w.setWindowTitle("LSI_Paint");
    w.setWindowIcon(QIcon(":/LSI"));
    w.showSplash(&splash);
    splash.finish(&w);
    w.showMaximized();
    return a.exec();
}
