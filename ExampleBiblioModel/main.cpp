#include "mainwindow.h"
#include <application.h>

/**
 * @brief qMain
 * @param argc
 * @param argv
 * @return
 * Главная функция по запуску приложения.
 */

int main(int argc, char *argv[])
{
    //QApplication  - главный класс приложения
    BIBLIO::Application App(argc, argv);
    BIBLIO::MainWindow w;
    w.show();

    return App.exec();
}
