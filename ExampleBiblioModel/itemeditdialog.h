#ifndef ITEMEDITDIALOG_H
#define ITEMEDITDIALOG_H

#include "data.h"


#include <QDialog>
#include <QFrame>
#include "itemeditframe.h"

class QPushButton ;

namespace BIBLIO {

namespace IED_HELPER {

//у вспомогательных классов можно не писать деструктор
//отработает деструктор внешнего класса
class Buttons: public QFrame {
    Q_OBJECT
private:
  QPushButton *pOK ;
  QPushButton *pCancel ;
public:
    Buttons( QWidget *parent=0);
//создание сигналов
signals:
    void accepting(void) ;
    void rejecting(void) ;
};

}//namespace IED_HELPER

/**
 * @brief Файл с объявлением диалогового окна -
 * "Редактирование данных об издании в отдельном окне".
 */

class ItemEditDialog : public QDialog
{
    Q_OBJECT

  private:
    ItemEditFrame       *Edt;
    IED_HELPER::Buttons *Btn;

  public:
    ItemEditDialog( QWidget *parent=0 );
    virtual ~ItemEditDialog();

    void attach(DATA::Object *X ) {Edt->attach(X) ;}

  protected:
    void closeEvent(QCloseEvent *E);
};

} //namespace BIBLIO


#endif // ITEMEDITDIALOG_H
