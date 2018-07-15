#include "table.h"
#include "application.h"
#include <QAction>
#include "itemeditdialog.h"

namespace BIBLIO {

Table::Table(QWidget *parent)
    : QTableView(parent) {
    setProperty("modeName","Table");

    setModel(APP->model());

    setContextMenuPolicy(Qt::ActionsContextMenu);
    {
        QAction *A = actEdit = new QAction(this);
        A->setText(tr("Edit"));
        connect(A,SIGNAL(triggered()),this,SLOT(itemEditCurrent()));
        addAction(A);
    }{
        QAction *A = actNew = new QAction(this);
        A->setText(tr("New"));
       connect(A,SIGNAL(triggered()),this,SLOT(itemCreateNew()));
        addAction(A);
    }{
        QAction *A = actDelete = new QAction(this);
        A->setText(tr("Delete"));
       connect(A,SIGNAL(triggered()),this,SLOT(itemDeleteCurrent()));
        addAction(A);
    }


}

Table::~Table() {

}

void Table::itemEditCurrent(void){
    //определяем какая строчка выбрана
    if (!selectedIndexes().first().isValid()) return;
    int row = selectedIndexes().first().row();
    DATA::Object *X = APP->model()->at(row);
    //создаём диалог
    ItemEditDialog Dia(this);
    //присоединяем данные к диалогу
    Dia.attach(X);
    Dia.exec();
}
void Table::itemCreateNew(void){

}
void Table::itemDeleteCurrent(void){

}

}//namespace BIBLIO
