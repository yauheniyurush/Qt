#include "catalogue.h"

#include <QAction>
#include <QMenu>
#include <QtSql>
#include <QMessageBox>


#include "posaction.h"

#define DATA_PTR(D,I,VALUE)                              \
    Item::Data *D = (Item::Data*) (I.internalPointer()); \
    if (!D) return VALUE;

#define DATE_STR(DATE) (                                        \
    DATE.isValid()  ? DATE.toString("dd.MM.yyyy") : QString()   \
)


namespace STORE {
namespace Catalogue {

/****************************************************************************/

Model::Model(QObject *parent) : QAbstractItemModel(parent), LastTempId(1) {

    QSqlQuery qry;
    qry.setForwardOnly(true);
    qry.prepare( "select            \n"
                   "iid,            \n"
                   "Code,           \n"
                   "Title,          \n"
                   "valid_from,     \n"
                   "valid_to,       \n"
                   "is_local,       \n"
                   "acomment,       \n"
                   "rid_parent,     \n"
                   "alevel          \n"
                   "from catalogue  \n"
                   "order by alevel; \n");
    if (qry.exec()) {
        while(qry.next()){
            bool OK = false;
            QVariant PI = qry.value("rid_parent");
            int ParentId = PI.toInt(&OK);
            Item::Data *P = 0;
            if (OK && !PI.isNull())  P = Cat.findPointer(ParentId);
            if (P) {
                Item::Data *D = new Item::Data(P, qry);
                P->Children.append(D);
                D->pParentItem = P ;
            } else {
                Item::Data *D = new Item::Data(this, qry);
                Cat.append(D);
                D->pParentItem = 0 ;
            }
        }
    } else {
        qCritical() << "Error";
        QSqlError Err = qry.lastError();
        qCritical() << Err.nativeErrorCode();
        qCritical() << Err.databaseText().toUtf8().data();
        qCritical() << Err.driverText().toUtf8().data();

    }


    //Это тестовый каталог. Заменить на настоящий
    /*
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
    }*/

}

Model::~Model(){

}

int Model::rowCount(const QModelIndex &parent) const{
    if (! parent.isValid()) {
        return Cat.size() ;//TODO заменить на правильное количество
    } else {
        DATA_PTR(P,parent,0);
        return P->Children.size();
    }
}

/****************************************************************************/

int Model::columnCount(const QModelIndex &parent) const{
   /*if (!parent.isValid())*/ return 6;
   //DATA_PTR(P,parent,0);
   //return P->Children.size() > 0 ? 6 : 0 ;
}

/****************************************************************************/

QVariant Model::dataDisplay(const QModelIndex &I) const{
    DATA_PTR(D,I,QVariant());
    //Item::Data *D = Cat[I.row()];
    switch (I.column() ) {
      case 1 : return D->Code ;
      case 0 : return D->Title ;
      case 2 : return DATE_STR(D->From);
                //D->From.isValid() ? D->From.toString("dd.MM.yyyy") : "" ;
      case 3 : return DATE_STR(D->To);
                //D->To.isValid() ? D->To.toString("dd.MM.yyyy") : "" ;
      case 4 : return D->IsLocal ? tr("LOCAL") : QString() ;
      case 5 : return D->Comment.isEmpty() ? QString() : tr("CMT") ;
      default : return QVariant();
    }
}

QVariant Model::dataTextAlignment(const QModelIndex &I) const{
    int Result = Qt::AlignVCenter;
    Result |= I.column() == 0 ? Qt::AlignLeft : Qt::AlignHCenter ;
    return Result;
}

//Item::Data * Model::dataDataBlock(const QModelIndex &I) const {
//    int R = I.row();
//    if (R < 0 || R >= Cat.size()) return 0;
//    return Cat[R];
//}

QVariant Model::dataFont(const QModelIndex &I) const {
    //Item::Data *D = dataDataBlock(I);
    //if (!D) return QVariant();
    DATA_PTR(D,I,QVariant());
    QFont F;
    if (D->Deleted) F.setStrikeOut(true);
    if (D->Changed) F.setItalic(true);
    return F;
}

QVariant Model::dataForeground(const QModelIndex &I) const {
    //Item::Data *D = dataDataBlock(I);
    //if (!D) return QVariant();
    DATA_PTR(D,I,QVariant());
    QColor Result = D->IsLocal ? QColor("blue") : QColor ("black") ;
    if (!D->isActive()) Result.setAlphaF(1.0/3.0);
    return Result;
    //if (!(D->To.isValid())) return QVariant();
    //if (D->To > QDateTime::currentDateTime()) {
    //    if (D->IsLocal) return QColor("#0000FF");
    //    else return QColor("#000000");
    //}
    //else {
    //    return QColor("#AAAAAA");
    //}
}

//*********************************************************************
//отвечает за фон строки
QVariant Model::dataBackground(const QModelIndex &I) const {
    DATA_PTR(D,I,QVariant());
    if (!D->isNew()) return QVariant();
    QColor Result = QColor("green") ;
    Result.setAlphaF(1.0/5.0);
    return Result;
}

QVariant Model::dataToolTip(const QModelIndex &I) const {
    //Item::Data *D = dataDataBlock(I);
    //if (!D) return QVariant();
    DATA_PTR(D,I,QVariant());
    switch (I.column()) case 2:{
        if (!D->To.isValid()) return QVariant();
        return tr("Valid to %1").arg(D->To.toString("dd.MM.yyyy"));

    default : return QVariant();
    }

    return QVariant("ToolTip");
}

//метод контролирующий отображение
QVariant Model::data(const QModelIndex &I, int role) const {

    switch (role) {
      case Qt::DisplayRole       : return dataDisplay(I);
      case Qt::TextAlignmentRole : return dataTextAlignment(I);
      case Qt::ForegroundRole    : return dataForeground(I);
      case Qt::FontRole          : return dataFont(I);
      case Qt::ToolTipRole          : return dataToolTip(I);
      //case Qt::UserRole          : return QVariant(dataDataBlock(I));
      //роль фона
      case Qt::BackgroundRole    : return dataBackground(I);
      case Qt::UserRole+1          : {
        //Item::Data *D =dataDataBlock(I);
        //if (!D) return false;
        DATA_PTR(D,I,false);
        return D->Deleted;
    }
      default : return QVariant();
    }

}

/****************************************************************************/

QVariant Model::headerData(int section,
                           Qt::Orientation orientation,
                           int role) const{
    if (orientation != Qt::Horizontal)
        return QAbstractItemModel::headerData(section,orientation,role);

    switch (role) {

    case Qt::DisplayRole :
    switch (section) {
      case 1 : return tr("Code")    ;
      case 0 : return tr("Title")   ;
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

void Model::delItem( const QModelIndex &I, QWidget *parent){
    //спросить у пользователя уверен ли он что хочет удалить элемент
    //Item::Data *D = dataDataBlock(I);
    //if (!D) return;
    DATA_PTR(D,I,);
    //to do исходим из того что модель линейна
    beginResetModel();//модель отправляет всем представлениям связанным с данной моделью сигнал о том что данные редактируются и представления не могут запрашивать данные на редактирование
    if (D->isNew()) {
    Item::Data *P = D->pParentItem ;
    if (P){
        P->Children.removeAt(I.row());
    } else {
        Cat.removeAt(I.row());
    }
    delete D;
    } else {
        D->Deleted = ! D->Deleted;
    }
    endResetModel();//окончание редактирвоания данных
}

void Model::editItem( const QModelIndex &I, QWidget *parent){
    Item::Dialog Dia( parent );
    //Item::Data *D = (Item::Data*)(I.internalPointer());//dataDataBlock(I);
    //if (!D) return;
    DATA_PTR(D,I,);
    Dia.setDataBlock(D);
    beginResetModel();//модель отправляет всем представлениям связанным с данной моделью сигнал о том что данные редактируются и представления не могут запрашивать данные на редактирование
    Dia.exec();
    endResetModel();//окончание редактирвоания данных
}

void Model::newItem( const QModelIndex &parentI, QWidget *parent){
    //if (parentI.isValid()) {
        //Сделать добавление нового элемента не обязательно в корень каталога
    //    qWarning()<<"Cannot add non top-level item";
    //    return;
    //}
    Item::Data *P = 0;
    if (parentI.isValid()) {
        P = (Item::Data*) (parentI.internalPointer());
        if (!P) {
            qWarning() << "Invalid internal pointer";
            return ;
        }
    }

    Item::Data *D = new Item::Data(this);
    if (!D) {
        qWarning() << "Cannot create new item";
        return;
    }
    Item::Dialog Dia( parent );
    Dia.setDataBlock(D);
    if (Dia.exec() == QDialog::Accepted) {
            beginResetModel();//модель отправляет всем представлениям связанным с данной моделью сигнал о том что данные редактируются и представления не могут запрашивать данные на редактирование
            if (P) {
              P->Children.append(D);
              D->pParentItem = P;
            } else {
              Cat.append(D);
            }
            //задаём динамическое свойство
            D->setProperty("temp_id", tempId());
            endResetModel();//окончание редактирвоания данных

    } else {
        delete D;
    }
}
/****************************************************************************/
TableView::TableView(QWidget *parent, Model *xModel) :QTableView(parent){

    Model *M = xModel ? xModel : new Model(this);
    setModel( M );

    {
        QHeaderView *H = verticalHeader() ;
        H->setSectionResizeMode(QHeaderView::ResizeToContents);//автоподбор высоты строк + высоту строк нельзя будет изменять
    }{
        QHeaderView *H = horizontalHeader() ;
        H->setSectionResizeMode(QHeaderView::ResizeToContents);//автоподбор высоты строк + высоту строк нельзя будет изменять
        H->setSectionResizeMode(0,QHeaderView::Stretch);
    }


    //вызов окна редактирования для строки по действию

    setContextMenuPolicy(Qt::CustomContextMenu);//объявили политику всплывающего меню

    connect(this,SIGNAL(customContextMenuRequested(QPoint)), //связали экшн вызова меню с нашим акшн contextMenuRequested
            this,SLOT(contextMenuRequested(QPoint)));

    {
        PosAction *A = actDelItem = new PosAction(this);
        A->setText(tr("delete"));
        connect(A,SIGNAL(editItem(QModelIndex,QWidget*)),
                M,SLOT(delItem(QModelIndex,QWidget*)) );
        addAction(A);
    }

    {
        PosAction *A = actNewItem = new PosAction(this);
        A->setText(tr("add"));
        connect(A,SIGNAL(editItem(QModelIndex,QWidget*)),
                M,SLOT(newItem(QModelIndex,QWidget*)) );
        addAction(A);
    }

    {
        PosAction *A = actEditItem =new PosAction(this);
        A->setText(tr("Edit"));
        connect(A,SIGNAL(editItem(QModelIndex,QWidget*)),
                M,SLOT(editItem(QModelIndex,QWidget*)) );
        addAction(A);
    }
    {
        PosAction *A = actRootItem =new PosAction(this);
        A->setText(tr("Show children"));
        connect(A,SIGNAL(editItem(QModelIndex, QWidget*)),
                this,SLOT(showChildren(QModelIndex, QWidget*)) );
        addAction(A);
    }
    {
        QAction *A = actParentRootItem =new QAction(this);
        A->setText(tr("Show parent"));
        connect(A,SIGNAL(triggered()), this,SLOT(showParent()) );
        addAction(A);
    }
    {
        QAction *A = actSave =new QAction(this);
        A->setText(tr("Save"));
        connect(A,SIGNAL(triggered()),
                M,SLOT(save()) );
        addAction(A);
    }

    //скрытие колонки
    setColumnHidden(3, true);
    setColumnHidden(4, true);

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
        actDelItem->I=I;
        actDelItem->pWidget=this;
        if (I.data(Qt::UserRole+1).toBool() ) {
            actDelItem->setText(tr("Restore"));
        }  else
        {
           actDelItem->setText(tr("Delete"));
        }
        M.addAction(actDelItem);
        actEditItem->I=I;
        actEditItem->pWidget = this;
        M.addAction(actEditItem);
        //добавим пункт меню по отображению дочерних записей
        actRootItem->I = I;
        actRootItem->pWidget = this;
        M.addAction(actRootItem) ;
    }
    actNewItem->I=rootIndex();
    actNewItem->pWidget=this;
    M.addAction(actNewItem);
    if (I.isValid()) {
        //добавим пункт меню по отображению дочерних записей
        actRootItem->I = I;
        actRootItem->pWidget = this;
        M.addAction(actRootItem) ;
    }
    if (rootIndex().isValid()) M.addAction(actParentRootItem);
    M.addAction(actSave);//экшн по сохранению
    M.exec(mapToGlobal(p));
}
/****************************************************************************/

QModelIndex Model::index(int row, int column,
                         const QModelIndex &parent) const {
    if (parent.isValid()) {
        //Item::Data *D = (Item::Data*);
        DATA_PTR(D,parent,QModelIndex());
        if (row < 0 || row >= D->Children.size() ) return QModelIndex() ;
        return createIndex(row,column,  (void*) (D->Children[row]));
    } else {
        if (row < 0 || row >= Cat.size()) return QModelIndex();
        return createIndex(row,column, (void*)(Cat[row]));
    }
}

QModelIndex Model::parent(const QModelIndex &I) const {
    DATA_PTR(D,I,QModelIndex());
    Item::Data *P = D->pParentItem;
    if (!P) {
        return QModelIndex();
    } else {
        int Row = -1;
        Item::Data *GP = P->pParentItem;
        if (GP) {
            for (int i =0; i < GP->Children.size(); i++) {
                if (GP->Children[i]->isSameAs(P)) {
                    Row = i;
                    break;
                }
            }
        } else {
            for (int i =0; i < Cat.size(); i++) {
                if (Cat[i]->isSameAs(P)) {
                    Row = i;
                    break;
                }
            }
        }
        if (Row<0){
            qWarning() << "Cannot find item";
            return QModelIndex();
        }
        return createIndex(Row, 0, P);
    }
}

//*******************************************************************************
//Сигнал  - для отображения древовидной структуры
void TableView::showChildren(const QModelIndex &I, QWidget *){
    setRootIndex(I);
}

//*******************************************************************************
//Сигнал  - для отображения древовидной структуры
void TableView::showParent(void){
    if (rootIndex().isValid()) setRootIndex(rootIndex().parent());
}

//*******************************************************************************
//Слот для сохранения данных в базу
void Model::save(){
    try {
    if (!delete_all()) throw (int)1;//удалить все элементы помеченные для удал
    if (!save_all()  ) throw (int)2;//сохранить измененённые эл-ты
    if (!insert_all()  ) throw (int)3;//сохранить новые эл-ты
    QMessageBox::information(0,tr("Info"),tr("Changes saved successfully"));
    //сохранить новые элементы
    } catch (int x){
        QMessageBox::critical(0, tr("Error"), tr("Cannot save changes"));
    }
}

//*****************************************************************
//функция для удаления из базы данных
bool Model::delete_all_from_db(Item::Data *D) {
    Item::List *Children = D ? &(D->Children) : &Cat ;
    Item::Data *X;
    foreach (X, *Children) {
        if (!delete_all_from_db(X)) return false;
    }
    if (!D) return true;
    if (! D->Deleted) return true;
    //формирование запроса лучше брать в скобки чтобы два запроса
    //одновременно в базе не висели
    {
        QSqlQuery DEL ;
        DEL.setForwardOnly(true);
        DEL.prepare("Delete from catalogue where iid = :IID ;");
        DEL.bindValue(":IID", D->Id) ;
        if (DEL.exec()) return true;
        qCritical() << DEL.lastError().databaseText();
        qCritical() << DEL.lastError().driverText();
        qCritical() << DEL.lastError().nativeErrorCode();
    }
    return false ;
}

//*****************************************************************
//функция для удаления из модели
bool Model::delete_all_from_model(Item::Data *D) {
    Item::List *Children = D ? &(D->Children) : &Cat ;
    bool Result = true;
    beginResetModel();
    for (int k = Children->size()-1; k>=0; k--) {
        if (Children->at(k)->Deleted) {
          Item::Data *X = Children->takeAt(k);
          delete X;
        } else {
          if (!delete_all_from_model(Children->at(k)))
              return false;
        }
    }
    endResetModel();
    return Result ;
}

//*****************************************************************
//основная функция для удаления
bool Model::delete_all() {
    bool R = true ;
    QSqlDatabase DB = QSqlDatabase::database();
    DB.transaction();
    if (delete_all_from_db())
    {
        DB.commit();
        return delete_all_from_model();
    }
    else {
        DB.rollback();
        return false;
    }
}

//*****************************************************************
//сохраняем изменения
bool Model::save_all_to_db(Item::Data *D){
    Item::List *Children = D ? &(D->Children) : &Cat ;
    Item::Data *X;
    foreach (X, *Children) {
        if (!save_all_to_db(X)) return false;
    }
    if (!D) return true;
    if (!D->Changed) return true;
    //формирование запроса лучше брать в скобки чтобы два запроса
    //одновременно в базе не висели
    {
        QSqlQuery UPD ;
        UPD.setForwardOnly(true);
        UPD.prepare("update catalogue set   \n"
                    "code       = :CODE   , \n"
                    "title      = :TITLE  , \n"
                    "valid_from = :FROM   , \n"
                    "valid_to   = :TO     , \n"
                    "is_local   = :LOCAL  , \n"
                    "acomment   = :COMMENT  \n"
                    "where iid  = :IID        ");
        UPD.bindValue(":CODE"   , D->Code   ) ;
        UPD.bindValue(":TITLE"  , D->Title  ) ;
        UPD.bindValue(":FROM"   , D->From   ) ;
        UPD.bindValue(":TO"     , D->To     ) ;
        UPD.bindValue(":LOCAL"  , D->IsLocal) ;
        UPD.bindValue(":COMMENT", D->Comment) ;
        UPD.bindValue(":IID"    , D->Id     ) ;
        if (UPD .exec()) return true;
        qCritical() << UPD.lastError().databaseText();
        qCritical() << UPD.lastError().driverText();
        qCritical() << UPD.lastError().nativeErrorCode();
    }
    return false ;
}

//*****************************************************************
//удаляем флаг что элемент менялся
bool Model::drop_change_mark(Item::Data *D){
    Item::List *Children = D ? &(D->Children) : &Cat ;
    Item::Data *X;
    foreach (X, *Children) {
        X->Changed=false;
        drop_change_mark(X);
    }
    return true;
}

//*****************************************************************
//основная функция удаления
bool Model::save_all(){
    QSqlDatabase DB = QSqlDatabase::database();
    DB.transaction();
    if (save_all_to_db())
    {
        DB.commit();
        return drop_change_mark();
    }
    else {
        DB.rollback();
        return false;
    }
}

//сохраняем новые элементы
bool Model::insert_all_to_db(Item::Data *D){
    bool must_be_saved = D ? D->isNew() : false;
    if (must_be_saved) {
        QSqlQuery INS ;
        INS.setForwardOnly(true);
        INS.prepare("insert into catalogue (\n"
                    "code, title,           \n"
                    "valid_from, valid_to,  \n"
                    "is_local, acomment,    \n"
                    "rid_parrent            \n"
                    ") values (             \n"
                    ":CODE, :TITLE,         \n"
                    ":FROM, :TO,            \n"
                    ":LOCAL, :COMMENT,      \n"
                    ":PARENT                \n"
                    ")returning iid,        \n"
                    "code, title,           \n"
                    "valid_from, valid_to,  \n"
                    "islocal, acomment,     \n"
                    "rid_parent, alevel;    \n"
                    );
        INS.bindValue(":CODE"   , D->Code   ) ;
        INS.bindValue(":TITLE"  , D->Title  ) ;
        INS.bindValue(":FROM"   , D->From   ) ;
        INS.bindValue(":TO"     , D->To     ) ;
        INS.bindValue(":LOCAL"  , D->IsLocal) ;
        INS.bindValue(":COMMENT", D->Comment) ;
    QVariant IdParent = QVariant();
    if (D->pParentItem)
        if (D->pParentItem->isNew()) {
            IdParent = D->pParentItem->property("new_id");
        } else
            IdParent = D->pParentItem->Id;
        INS.bindValue(":PARENT", IdParent) ;
        if (!INS .exec()) {
            qCritical() << INS.lastError().databaseText().toUtf8().data();
            qCritical() << INS.lastError().driverText();
            qCritical() << INS.lastError().nativeErrorCode();
            return false;
        }
        while (INS.next()) {
            D->Code    = INS.value ("code"      ).toString();
            D->Title   = INS.value ("title"     ).toString();
            D->From    = INS.value ("valid_from").toDateTime();
            D->To      = INS.value ("valid_to"  ).toDateTime();
            D->IsLocal = INS.value ("islocal"   ).toBool();
            D->Comment = INS.value ("acomment"   ).toString();
            qDebug() << INS.value("rid_parent") << INS.value("alevel");
            D->setProperty("new_id", INS.value("iid"));
        }
    }{
        Item::List *Children = D ? &(D->Children) : &Cat ;
        Item::Data *X;
        foreach (X, *Children) {
            if (!insert_all_to_db(X))
                return false;
        }
    }
    return true;
}

//сохраняем новые элементы
bool Model::adjust_id_for_new(Item::Data *D){
    bool must_be_saved = D ? D->isNew() : false;
    if (must_be_saved) {
        D->Id = D->property("new_id");
    }
    Item::List *Children = D ? &(D->Children) : &Cat ;
    Item::Data *X;
    foreach (X, *Children) {
        if (!adjust_id_for_new(X))
            return false;
    }
    return true;
}

//основная функция добавления
bool Model::insert_all(){
    QSqlDatabase DB = QSqlDatabase::database();
    DB.transaction();
    if (insert_all_to_db())
    {
        DB.commit();
        return adjust_id_for_new();
    }
    else {
        DB.rollback();
        return false;
    }
}


TreeView::TreeView(QWidget *parent, Model *xModel)
    :QTreeView(parent) {

    Model *M = xModel ? xModel : new Model(this);
    setModel(M);

}

TreeView::~TreeView(){

}



ColumnView::ColumnView(QWidget *parent, Model *xModel)
    :QColumnView(parent) {

    Model *M = xModel ? xModel : new Model(this);
    setModel(M);

    QList<int> L ;
    L<<200<<200<<200<<200<<200<<200<<200<<200<<200<<200;
    setColumnWidths(L);

}

ColumnView::~ColumnView(){

}



}//Catalogue
}//namespace STORE
