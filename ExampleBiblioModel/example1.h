#ifndef EXAMPLE1_H
#define EXAMPLE1_H

#include <QDialog>
#include "ui_example1.h"// НАДО ДОБАВИТЬ ЧТОБЫ ПОДВЯЗАТЬ ФОРМУ

namespace BIBLIO {

class example1 : public QDialog
{
    Q_OBJECT

private:
    Ui::example1 ui;// НАДО ДОБАВИТЬ ЧТОБЫ ПОДВЯЗАТЬ ФОРМУ

public:
    example1(QWidget *parent=0);

};

}//namespace BIBLIO

#endif // EXAMPLE1_H
