#ifndef CATITEMEDIT_H
#define CATITEMEDIT_H

#include "ui_catitemframe.h"
#include <QFrame>

#include "dialogtpl.h"

namespace STORE {
namespace Catalogue {
namespace Item {

/***************************************************/


class Data : public QObject {

    Q_OBJECT

public:
    QString   Code   ;
    QString   Title  ;
    QDateTime From   ;
    QDateTime To     ;
    bool      IsLocal;
    Data      *pParentItem ;
};


/***************************************************/
class Frame : public QFrame {

    Q_OBJECT

public:
    Frame(QWidget *parent=0);
    virtual ~Frame();

private:
  Ui::CatItemFrame ui;

public slots:
  void is_good(bool *pOK);

};

/***************************************************/
class Dialog: public CommonDialog {

    Q_OBJECT

private:
    Frame *pFrame;

public:
    Dialog(QWidget *parent=0);
    virtual ~Dialog();

};

/***************************************************/




} // namespace Item
} // namespace Catalogue
} // namespace STORE

#endif // CATITEMEDIT_H
