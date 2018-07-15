#include "itemeditdialog.h"
#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QWidget>
#include <QCloseEvent>

namespace BIBLIO {

/**
 * @brief Реализация класса окна редактирования
 * @param parent
 */

namespace IED_HELPER {

Buttons::Buttons(QWidget *parent) :QFrame(parent) {

    setFrameStyle(StyledPanel | Sunken);
    setSizePolicy(QSizePolicy::Expanding,//по горизонтали
                  QSizePolicy::Minimum); //по вертикали
    QHBoxLayout *L = new QHBoxLayout(this);
    L->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,//элемент занимающий пустое пространство
                                   QSizePolicy::Minimum));//и двигающий кнопки влево до упора
    {
     QPushButton *B = pOK = new QPushButton(this);
     L->addWidget(B);
     B->setText(tr("OK"));
     //закрытие окна диалога по хорошему
     connect(B,SIGNAL(clicked()), this, SIGNAL(accepting()));
    }{
        QPushButton *B = pCancel = new QPushButton(this);
        L->addWidget(B);
        B->setText(tr("Cancel"));
        //закрытие окна диалога по плохому
        connect(B,SIGNAL(clicked()), this, SIGNAL(rejecting()));
    }

}

}//namespace IED_HELPER

ItemEditDialog::ItemEditDialog( QWidget *parent ) : QDialog (parent)
{
    setWindowTitle(tr("Editing a reference"));

    QVBoxLayout *L0 = new QVBoxLayout(this);
    {//верхний фрэйм
        Edt = new ItemEditFrame(this);
        L0->addWidget(Edt);
        //вот так мы ставили фрейм-заглушку
        //QFrame *F = new QFrame(this);
        //F->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
        //F->setSizePolicy(QSizePolicy::Expanding,//политика размеров фрэйма по горизонтали
        //                 QSizePolicy::Expanding); //по вертикали
        //L0->addWidget(F);
    }{//нижний фрэйм
     Btn = new IED_HELPER::Buttons( this ) ;
     L0->addWidget(Btn);
     connect( Btn,SIGNAL(accepting()),this,SLOT(accept()) );
     connect( Btn,SIGNAL(rejecting()),this,SLOT(reject()) );
    }
}

ItemEditDialog::~ItemEditDialog(){

}

void ItemEditDialog::closeEvent(QCloseEvent *E){
    switch (result()) {
        case Rejected:
        E->accept();
        break;
    case Accepted: if (Edt->isValid()) {
                     Edt->save();
                     E->accept();
                   }
                   else E->ignore();
        break;
        default:
        E->accept();
        break;
    }
}


}//namespace BIBLIO
