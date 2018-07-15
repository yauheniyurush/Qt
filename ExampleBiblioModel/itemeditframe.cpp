#include "itemeditframe.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <helpers.h>
#include<QComboBox>
#include"items.h"
#include<QTextEdit>
#include<QIntValidator>

namespace BIBLIO {

ItemEditFrame::ItemEditFrame(QWidget *parent):QFrame (parent)
{

    Dt = 0;

    setFrameStyle(StyledPanel | Sunken);
    setSizePolicy(QSizePolicy::Expanding,
                  QSizePolicy::Expanding);

    QVBoxLayout *L = new QVBoxLayout(this);

    setup_Author(L);
    setup_Title(L);
    setup_SubTitle(L);

    {
        QHBoxLayout *L1 = new QHBoxLayout(this);
        L->addLayout(L1);
        L1->setMargin(0);
        setup_Publisher(L1);
        setup_Location(L1);
        setup_Year(L1);
        setup_TotalPages(L1);
    }

    setup_Kind(L);
    setup_Comment(L);

    cbxKind->currentIndexChanged(0);

}
//стандартная функция которая добавляет элемент типа редактирования (лэйбл+строка редактирования)
void ItemEditFrame::setup_Author(QLayout *L)
{
    QVBoxLayout *L1 = new QVBoxLayout();
    L1->setSpacing(0);//расстояние между элементами раскладки
    L1->setMargin(0);//свободное поле вокруг рамки
    L->addItem(L1);

    QLabel *lbl = new QLabel(this);
    //hlp::setHorPolicy(lbl,QSizePolicy::Minimum);
    //hlp::setWidth(lbl,10);
    lbl->setText( tr("Author") );
    L1->addWidget(lbl);

    QLineEdit *txt = edtAutor = new QLineEdit(this);
    //hlp::setWidth(txt,10);
    L1->addWidget(txt);
}

void ItemEditFrame::setup_Title(QLayout *L)
{
    QVBoxLayout *L1 = new QVBoxLayout();
    L1->setSpacing(0);
    L1->setMargin(0);
    L->addItem(L1);

    QLabel *lbl = new QLabel(this);
    lbl->setText( tr("Title") );
    L1->addWidget(lbl);

    QLineEdit *txt = edtTitle = new QLineEdit(this);
    L1->addWidget(txt);
}

void ItemEditFrame::setup_SubTitle(QLayout *L)
{
    QVBoxLayout *L1 = new QVBoxLayout();
    L1->setSpacing(0);//расстояние между элементами раскладки
    L1->setMargin(0);//свободное поле вокруг рамки
    L->addItem(L1);

    QLabel *lbl = new QLabel(this);
    lbl->setText( tr("Subtitle") );
    L1->addWidget(lbl);

    QLineEdit *txt = new QLineEdit(this);
    L1->addWidget(txt);
}

void ItemEditFrame::setup_Publisher(QLayout *L)
{
    QVBoxLayout *L1 = new QVBoxLayout();
    L1->setSpacing(0);//расстояние между элементами раскладки
    L1->setMargin(0);//свободное поле вокруг рамки
    L->addItem(L1);

    QLabel *lbl = new QLabel(this);
    lbl->setText( tr("Publisher") );
    L1->addWidget(lbl);

    QLineEdit *txt = new QLineEdit(this);
    L1->addWidget(txt);
}

void ItemEditFrame::setup_Location(QLayout *L)
{
    QVBoxLayout *L1 = new QVBoxLayout();
    L1->setSpacing(0);//расстояние между элементами раскладки
    L1->setMargin(0);//свободное поле вокруг рамки
    L->addItem(L1);

    QLabel *lbl = new QLabel(this);
    lbl->setText( tr("Location") );
    L1->addWidget(lbl);

    QLineEdit *txt = new QLineEdit(this);
    L1->addWidget(txt);
}

void ItemEditFrame::setup_Year(QLayout *L)
{
    QVBoxLayout *L1 = new QVBoxLayout();
    L1->setSpacing(0);//расстояние между элементами раскладки
    L1->setMargin(0);//свободное поле вокруг рамки
    L->addItem(L1);

    QLabel *lbl = new QLabel(this);
    lbl->setText( tr("Year") );
    hlp::setHorPolicy(lbl,QSizePolicy::Minimum);
    hlp::setWidth(lbl, 100);
    L1->addWidget(lbl);

    QLineEdit *txt = new QLineEdit(this);
    hlp::setHorPolicy(txt,QSizePolicy::Minimum);
    hlp::setWidth(txt, 100);
    L1->addWidget(txt);
}


void ItemEditFrame::setup_TotalPages(QLayout *L)
{
    QVBoxLayout *L1 = new QVBoxLayout();
    L1->setSpacing(0);//расстояние между элементами раскладки
    L1->setMargin(0);//свободное поле вокруг рамки
    L->addItem(L1);

    QLabel *lbl = lblTotalPages = new QLabel(this);
    lbl->setText( tr("TotalPages") );
    L1->addWidget(lbl);

    QLineEdit *txt = edtTotalPages = new QLineEdit(this);
    //ставим валидатор на это поле, валидатор не позволяет вводить заведомо неверное число
    txt->setValidator(new QIntValidator(0,1000000));
    L1->addWidget(txt);
}

void ItemEditFrame::setup_Kind(QLayout *L)
{
    QHBoxLayout *L1 = new QHBoxLayout();
    L->addItem(L1);

    QSpacerItem *Sp = new QSpacerItem(0,0,QSizePolicy::Expanding);
    L1->addItem(Sp);

    QComboBox *cbx = cbxKind = new QComboBox(this);
    //добавляем в комбобокс содержимое
    cbx->addItem(tr("---"),Unknown);
    cbx->addItem(tr("Book"),Book);
    cbx->addItem(tr("Article"),Article);
    cbx->setCurrentIndex(0);
    connect(cbx,SIGNAL(currentIndexChanged(int)),
            this,SLOT(kindSelected(int)));
    L1->addWidget(cbx);
}

void ItemEditFrame::kindSelected(int index){
    //dynamic_cast выполняет преобразование экземпляра полиморфного класса
    //в класс который мы указали
    QComboBox *C = dynamic_cast<QComboBox*>(sender());//sender возвращает объект вызвавший слот, пославший сигнал, функция работает только в слотах
    //проверяем от комбобокса ли пришло сообщение, если нет - выходим
    if ( ! C ) {
        // @TODO Здесь написать сообщение в лог
        return;
    }
    //если от комбобокса
    bool OK = false;
    int K = C->itemData(index).toInt(&OK);
    if ( ! OK ) {
        // @TODO Здесь написать сообщение в лог
        return;
    }

    switch ( K )
    {
    case Unknown:
        lblTotalPages->setVisible(true);
        lblTotalPages->setEnabled(false);
        edtTotalPages->setVisible(true);
        edtTotalPages->setEnabled(false);
        break;

    case Book:
        lblTotalPages->setVisible(true);
        lblTotalPages->setEnabled(true);
        edtTotalPages->setVisible(true);
        edtTotalPages->setEnabled(true);
        break;
    case Article:
        lblTotalPages->setVisible(false);
        lblTotalPages->setEnabled(false);
        edtTotalPages->setVisible(false);
        edtTotalPages->setEnabled(false);
        break;
    default:
         // @TODO Здесь написать сообщение в лог
        return;
    }
}

void ItemEditFrame::setup_Comment(QLayout *L)
{
    QVBoxLayout *L1 = new QVBoxLayout();
    L1->setSpacing(0);//расстояние между элементами раскладки
    L1->setMargin(0);//свободное поле вокруг рамки
    L->addItem(L1);

    QLabel *lbl = new QLabel(this);
    lbl->setText( tr("Comment") );
    L1->addWidget(lbl);

    QTextEdit *txt = new QTextEdit(this);
    L1->addWidget(txt);
}

ItemEditFrame::~ItemEditFrame()
{

}

void ItemEditFrame::attach(DATA::Object *X)  {
    Dt = X;
    if (!Dt) return;
    //Общая часть
    edtAutor->setText(X->Autor);
    edtTitle->setText(X->Title);
    //Для книги
    {
        DATA::Book *B = dynamic_cast<DATA::Book*>(X);
        if (B) {
            QString N;
            N.setNum(B->TotalPages);
            edtTotalPages->setText(N);
            int k = cbxKind->findData(Book);
            if (k>=0) cbxKind->setCurrentIndex(k);
            cbxKind->setEnabled(false);
        }
    }{
        DATA::Article *B = dynamic_cast<DATA::Article*>(X);
        if (B) {
            int k = cbxKind->findData(Article);
            if (k>=0) cbxKind->setCurrentIndex(k);
            cbxKind->setEnabled(false);
        }
    }

}

void ItemEditFrame::save (void) {

}

bool ItemEditFrame::isValid() const {
    if (edtTitle->text().size()<=0) return true;
    return edtTitle->text().at(0) != '.';
}

} //namespace BIBLIO
