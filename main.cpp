#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>



int main(int argc, char *argv[])
{
    srand (time(NULL));
    glutInit(&argc,argv);
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "nienazwany_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
//    if(translator.load("nieznany_PL.ts"))
//    {
//        a.installTranslator(&translator);
//    }
    MainWindow w;
    w.show();

    return a.exec();


}
