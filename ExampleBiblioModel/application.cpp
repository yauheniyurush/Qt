#include "application.h"

#include <QTranslator>

namespace  BIBLIO {

/**
 * @brief Application::Application
 * @param argc
 * @param argv
 * Файл реализации своего класса приложения.
 */

Application::Application(int argc, char *argv[])
    : QApplication( argc, argv){

    //установка перевода приложения
    pTranslator = new QTranslator(this);
    pTranslator->load(":/lang/rus");
    installTranslator(pTranslator);

    // это ещё надо разобрать
    pModel = new BiblioModel(this);

}

Application::~Application()
{

}

}//BIBIO
