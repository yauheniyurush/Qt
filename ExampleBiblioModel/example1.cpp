#include "example1.h"

namespace BIBLIO {

example1::example1(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);// НАДО ДОБАВИТЬ ЧТОБЫ ПОДВЯЗАТЬ ФОРМУ
    ui.cbxCurrent->addItem(tr("Vasya"),1);
    ui.cbxCurrent->addItem(tr("Petya"),2);
}

}//namespace BIBLIO
