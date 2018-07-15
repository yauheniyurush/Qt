#ifndef ITEMEDITFRAME_H
#define ITEMEDITFRAME_H

#include <QFrame>
#include "Data.h"

class QVBoxLayout;
class QLabel;
class QLineEdit;
class QComboBox;

namespace BIBLIO {



class ItemEditFrame : public QFrame
{
    Q_OBJECT

  private:
    DATA::Object *Dt;

    QLabel       *lblTotalPages;
    QLineEdit    *edtTotalPages;
    void setup_TotalPages (QLayout *L);

    QLineEdit *edtAutor;
    void setup_Author     (QLayout *L);

    QLineEdit *edtTitle;
    void setup_Title      (QLayout *L);
    void setup_SubTitle   (QLayout *L);
    void setup_Location   (QLayout *L);
    void setup_Publisher  (QLayout *L);
    void setup_Year       (QLayout *L);

    QComboBox *cbxKind;
    void setup_Kind       (QLayout *L);
    void setup_Comment    (QLayout *L);

  protected slots:
    void kindSelected (int index);

  public:
    ItemEditFrame(QWidget *parent=0);
    virtual ~ItemEditFrame();

    void attach(DATA::Object *X)  ;
    void save (void) ;

    bool isValid() const ;
};

} //namespace BIBLIO

#endif // ITEMEDITFRAME_H
