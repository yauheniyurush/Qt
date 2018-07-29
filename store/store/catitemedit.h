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
    Data(QObject *parent=0):QObject(parent) {}

    QString   Code   ;
    QString   Title  ;
    QDateTime From   ;
    QDateTime To     ;
    QString   Comment;
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

public:
  Data *Block ;

public:
  void setDataBlock(Data *D) {
      Block = D;
      load();
  }

public slots:
  void is_good(bool *pOK);
  void load() ;//perenos inf s dannih na dialog
  bool save() ;//perenos inf s dialoga na dannie

signals:
  void error_message(const QString &);



};

/***************************************************/
class Dialog: public CommonDialog {

    Q_OBJECT

private:
    Frame *pFrame;

public:
    Dialog(QWidget *parent=0);
    virtual ~Dialog();

public:
    void setDataBlock(Data *D){ pFrame->setDataBlock(D); }

};

/***************************************************/




} // namespace Item
} // namespace Catalogue
} // namespace STORE

#endif // CATITEMEDIT_H
