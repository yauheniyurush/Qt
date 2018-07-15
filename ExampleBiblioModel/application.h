#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "bibliomodel.h"

/**
 * Файлобъявления своего класса приложения.
 */

class QTranslator;

namespace BIBLIO {

class Application : public QApplication
{
    Q_OBJECT

private:
    QTranslator *pTranslator;
    BiblioModel *pModel;

public:
    Application( int argc, char *argv[]);
    virtual ~Application();
    BiblioModel *model() {return pModel;}
};

#define APP dynamic_cast< ::BIBLIO::Application*>(qApp)

} //BIBLIO

#endif // APPLICATION_H
