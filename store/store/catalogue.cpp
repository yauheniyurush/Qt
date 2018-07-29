#include "catalogue.h"

#include <QAction>
#include <QMenu>

#include "posaction.h"

namespace STORE {
namespace Catalogue {

/****************************************************************************/

class PositionedAction : public QAction {
    Q_OBJECT
};
/****************************************************************************/

Model::Model(QObject *parent) : QAbstractTableModel(parent) {

    //Это тестовый каталог. Заменить на настоящий
    {
        Item::Data *D = new Item::Data(this);
        D->Code = "111";
        D->Title = "Физика";
        D->From = QDateTime::currentDateTime();
        D->To = QDateTime();
        D->IsLocal = false ;
        Cat.append(D);
    }{
        Item::Data *D = new Item::Data(this);
        D->Code = "222";
        D->Title = "Математика";
        D->From = QDateTime::currentDateTime();
        D->To = QDateTime();
        D->IsLocal = false ;
        Cat.append(D);
    }{
        Item::Data *D = new Item::Data(this);
        D->Code = "333";
        D->Title = "Биология";
        D->From = QDateTime::currentDateTime();
        D->To = QDateTime();
        D->IsLocal = false ;
        Cat.append(D);
    }{
        Item::Data *D = new Item::Data(this);
        D->Code = "444";
        D->Title = "Валеология";
        D->From = QDateTime::currentDateTime();
        D->To = QDateTime();
        D->IsLocal = true ;
        Cat.append(D);
    }{
        Item::Data *D = new Item::Data(this);
        D->Code = "555";
        D->Title = "Литература";
        D->From = QDateTime::currentDateTime();
        D->To = QDateTime();
        D->IsLocal = false ;
        D->Comment = "Проверить правильность";
        Cat.append(D);
    }

}

Model::~Model(){

}

int Model::rowCount(const QModelIndex &parent) const{
    if (! parent.isValid()) {
        return Cat.size() ;//TODO заменить на правильное количество
    } else {
        return 0;
    }
}

/****************************************************************************/

int Model::columnCount(const QModelIndex &parent) const{
    if (! parent.isValid()) {
        return 6 ;
    } else {
        return 0;
    }
}

/****************************************************************************/

QVariant Model::dataDisplay(const QModelIndex &I) const{
    Item::Data *D = Cat[I.row()];
    switch (I.column() ) {
      case 0 : return D->Code ;
      case 1 : return D->Title ;
      case 2 : return D->From ;
      case 3 : return D->To ;
      case 4 : return D->IsLocal ? tr("LOCAL") : QString() ;
      case 5 : return D->Comment.isEmpty() ? QString() : tr("CMT") ;
      default : return QVariant();
    }
}

QVariant Model::dataTextAlignment(const QModelIndex &I) const{
    int Result = Qt::AlignVCenter;
    Result |= I.column() == 1 ? Qt::AlignLeft : Qt::AlignHCenter ;
    return Result;
}

Item::Data * Model::dataDataBlock(const QModelIndex &I) const {
    int R = I.row();
    if (R < 0 || R >= Cat.size()) return 0;
    return Cat[R];
}

QVariant Model::data(const QModelIndex &I, int role) const {

    switch (role) {
      case Qt::DisplayRole : return dataDisplay(I);
      case Qt::TextAlignmentRole : return dataTextAlignment(I);
      default : return QVariant();
    }

}

/****************************************************************************/

QVariant Model::headerData(int section,
                           Qt::Orientation orientation,
                           int role) const{
    if (orientation != Qt::Horizontal)
        return QAbstractTableModel::headerData(section,orientation,role);

    switch (role) {

    case Qt::DisplayRole :
    switch (section) {
      case 0 : return tr("Code")    ;
      case 1 : return tr("Title")   ;
      case 2 : return tr("From")    ;
      case 3 : return tr("To")      ;
      case 4 : return tr("Is Local");
      default : return QVariant()   ;
    }

    case Qt::TextAlignmentRole :
        return QVariant(Qt::AlignBaseline | Qt::AlignCenter) ;

    case Qt::ForegroundRole :
    { //Сделать шрифт жирным
        QFont F;
        F.setBold(true);
        return F;
    }

    default : return QVariant();

    }

}

void Model::editItem( const QModelIndex &I, QWidget *parent){
    Item::Dialog Dia( parent );
    Item::Data *D = dataDataBlock(I);
    if (!D) return;
    Dia.setDataBlock(D);
    beginResetModel();//модель отправляет всем представлениям связанным с данной моделью сигнал о том что данные редактируются и представления не могут запрашивать данные на редактирование
    Dia.exec();
    endResetModel();//окончание редактирвоания данных
}

/****************************************************************************/
TableView::TableView(QWidget *parent) :QTableView(parent){

    Model *M = new Model(this);
    setModel( M );

    {
        QHeaderView *H = verticalHeader() ;
        H->setSectionResizeMode(QHeaderView::ResizeToContents);//автоподбор высоты строк + высоту строк нельзя будет изменять
    }{
        QHeaderView *H = horizontalHeader() ;
        H->setSectionResizeMode(QHeaderView::ResizeToContents);//автоподбор высоты строк + высоту строк нельзя будет изменять
        H->setSectionResizeMode(1,QHeaderView::Stretch);
    }


    //вызов окна редактирования для строки по действию

    setContextMenuPolicy(Qt::CustomContextMenu);//объявили политику всплывающего меню

    connect(this,SIGNAL(customContextMenuRequested(QPoint)), //связали экшн вызова меню с нашим акшн contextMenuRequested
            this,SLOT(contextMenuRequested(QPoint)));

    {
        PosAction *A = actEditItem =new PosAction(this);
        A->setText(tr("Edit"));
        connect(A,SIGNAL(editItem(QModelIndex,QWidget*)),
                M,SLOT(editItem(QModelIndex,QWidget*)) );
        addAction(A);
    }

}

TableView::~TableView(){

}

//вызов окна редактирования Слот для action
//void TableView::editItem(){
//}

//пишем свою функцию по отображению меню
void TableView::contextMenuRequested(const QPoint &p) {
    QMenu M(this);
    QModelIndex I = indexAt(p);
    if (I.isValid()) {
        actEditItem->I=I;
        actEditItem->pWidget = this;
        M.addAction(actEditItem);
    }
    M.exec(mapToGlobal(p));
}
/****************************************************************************/
}//Catalogue
}//namespace STORE
