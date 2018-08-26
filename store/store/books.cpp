#include "books.h"
#include <QtSql>
#include <QtDebug>
#include <QHeaderView>
#include <QAction>
#include <QPainter>

namespace {
void REPORT_ERROR(QSqlQuery &QUERY) {
    qDebug() <<  QUERY.executedQuery().toUtf8().data();
    qCritical() <<  QUERY.lastError().databaseText().toUtf8().data();
}
} //namespace

namespace STORE {
namespace Books {


/*****************************************************************/
//класс делегата для редактирования статуса

StatusDelegate::StatusDelegate(QObject *parent,
               const QMap<int,QString> &AllStatus)
    :QItemDelegate(parent), fAllStatus(AllStatus) {
}

/*----------------------------------------------------------------*/

QWidget * StatusDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &I) const{
    QComboBox *CB = new QComboBox(parent);
    QMapIterator<int,QString> K(fAllStatus);
    CB->addItem(QString(), QVariant());
    while (K.hasNext()) {
        K.next();
        CB->addItem(K.value(),K.key());
    }
    return CB;
}

/*----------------------------------------------------------------*/

void StatusDelegate::setEditorData(QWidget *editor,
                   const QModelIndex &I) const{
  QComboBox *CB = qobject_cast<QComboBox*>(editor);
  if (!CB) return;

  QVariant IdStatus = I.data(Qt::EditRole);

  if (!IdStatus.isValid()){
      CB->setCurrentIndex(0);
      return;
  }

  for (int k=1;k<CB->count();k++){
      if (CB->itemData(k) == IdStatus) {
          CB->setCurrentIndex(k);
          break;
      }
  }
}

/*----------------------------------------------------------------*/

void StatusDelegate::setModelData(QWidget * editor,
                  QAbstractItemModel *model,
                  const QModelIndex &I) const{
    QComboBox *CB = qobject_cast<QComboBox*>(editor);
    if (!CB) return;
    model->setData(I,CB->currentData(), Qt::EditRole);
}

/*----------------------------------------------------------------*/

void StatusDelegate::paint(QPainter *painter,
                            const QStyleOptionViewItem &option,
                           const QModelIndex &I) const{
    QItemDelegate::paint(painter,option,I);
    if (I.data(Qt::EditRole) != -2) return;

    painter->setBrush(QBrush(QColor("black"),Qt::DiagCrossPattern));
    painter->setPen(Qt::NoPen);
    painter->drawRect(option.rect);

}

/*****************************************************************/


Model_EditOnServer::Model_EditOnServer(QObject *parent)
    :QSqlTableModel(parent) {

    setEditStrategy(OnFieldChange);//установка стратегии редактирования

    {
        QAction *A = actDeleteRow = new QAction(this);
        A->setText(tr("Delete"));
        connect(A,SIGNAL(triggered()),this,SLOT(on_delete_row()));
        AllActions << A;
    }{
        QAction *A = actNewRow = new QAction(this);
        A->setText(tr("New"));
        connect(A,SIGNAL(triggered()),this,SLOT(on_new_row()));
        AllActions << A;
    }{
        QAction *A = actSaveAll = new QAction(this);
        A->setText(tr("Save"));
        connect(A,SIGNAL(triggered()),this,SLOT(on_save_row()));
        AllActions << A;
    }{
        QAction *A = actRestoreAll = new QAction(this);
        A->setText(tr("Restore"));
        connect(A,SIGNAL(triggered()),this,SLOT(on_restore_row()));
        AllActions << A;
    }

    {
        QSqlQuery QUERY;
        QUERY.prepare("select iid,title from status;");
        bool OK = QUERY.exec();
        if (!OK) {
            REPORT_ERROR(QUERY);
            return;
        }
        while (QUERY.next()) {
            int Id = QUERY.value("iid").toInt();
            AllStatus[Id] = QUERY.value("title").toString();
        }
    }

}

void Model_EditOnServer::on_save_all(){

}
void Model_EditOnServer::on_restore_all(){

}
void Model_EditOnServer::on_delete_row(){

}
void Model_EditOnServer::on_new_row(){
    insertRow(0);
    setData(index(0,1),fCatId,Qt::EditRole);
}

void Model_EditOnServer::cat_item_selected(QVariant Id){
       fCatId = Id;
       adjust_query();

}

void Model_EditOnServer::apply_filter(QObject *F){
    fAuthor = F->property("author");
    fTitle = F->property("title");
    fYear = F->property("year");
    adjust_query();
}

void Model_EditOnServer::adjust_query(){

    setTable(QString());

    {
        QSqlQuery DROP;
        bool OK = DROP.exec("drop table if exists my_books;");
        if (!OK) {
            REPORT_ERROR(DROP);
            return;
        }
    }

    {
        QSqlQuery CREATE;
        bool OK = CREATE.exec("create temporary table my_books ( \n "
                       "iid bigint primary key,            \n"
                       "rid_catalogue bigint,  \n"
                       "author text,         \n"
                       "title text,          \n"
                       "eyear int,          \n"
                       "location text,       \n"
                       "publisher text,      \n"
                       "pages int,          \n"
                       "annote text,         \n"
                       "rid_status bigint,      \n"
                       "status_title text,           \n"
                       "acomment text );        ");
        if (!OK) {
                REPORT_ERROR(CREATE);
            return;
        }
    }

    {
    QString QueryText = "insert into my_books ("
                        "iid ,            \n"
                        "rid_catalogue,  \n"
                        "author ,         \n"
                        "title ,          \n"
                        "eyear ,          \n"
                        "location ,       \n"
                        "publisher ,      \n"
                        "pages ,          \n"
                        "annote,         \n"
                        "rid_status ,      \n"
                        "status_title ,           \n"
                        "acomment )  \n"
            "select            \n"
                    "b.iid,            \n"
                    "b.rid_catalogue,  \n"
                    "b.author,         \n"
                    "b.title,          \n"
                    "b.eyear,          \n"
                    "b.location,       \n"
                    "b.publisher,      \n"
                    "b.pages,          \n"
                    "b.annote,         \n"
                    "b.rid_status,      \n"
                    "s.title as status_title,           \n"
                    "b.acomment          \n"
                    "from books b      \n"
                    "left outer join status s \n"
                    "on b.rid_status = s.iid      \n"
                    "where b.rid_catalogue = :CID \n";
     if (fAuthor.isValid()) QueryText += "and b.author ~ :AUTHOR \n";
     if (fTitle.isValid()) QueryText += "and b.title ~ :TITLE \n";
     if (fYear.isValid()) QueryText += "and b.eyear = :YEAR \n";
     QueryText += "; \n";

     QSqlQuery qry;
     qry.prepare(QueryText);
     qry.bindValue(":CID", fCatId);
     if (fAuthor.isValid()) qry.bindValue(":AUTHOR","^"+fAuthor.toString());
     if (fTitle.isValid()) qry.bindValue(":TITLE",fTitle);
     if (fYear.isValid()) qry.bindValue(":YEAR",fYear);
     if ( !qry.exec() ) {
         REPORT_ERROR(qry);
         return;
     }
    }

     setTable("my_books");
     if ( !select() ){
         qCritical() << "Error selected";
     } else {
         qDebug() << "selected sucsessful";
     }
}

Model_EditOnServer::~Model_EditOnServer(){

}





//-----------------------------------------------------
Model::Model(QObject *parent)
    :QSqlQueryModel(parent) {


}

Qt::ItemFlags Model_EditOnServer::flags(const QModelIndex &I) const {
    Qt::ItemFlags Result = Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
    if (I.column() != 0)
        Result |= Qt::ItemIsEditable;
    return Result;

}

QVariant Model_EditOnServer::data(const QModelIndex &idx, int role) const{
    if (! idx.isValid()) return QSqlTableModel::data(idx,role);
    if (role !=Qt::EditRole) return QSqlTableModel::data(idx,role);
    if (idx.column() != 10) return QSqlTableModel::data(idx,role);
    return QSqlTableModel::data(index(idx.row(),9),role);
}

bool Model_EditOnServer::setData(const QModelIndex &I, const QVariant &value, int role){
    if (! I.isValid()) return QSqlTableModel::setData(I,value,role);
    if (role !=Qt::EditRole) return QSqlTableModel::setData(I,value,role);
    if (I.column() != 10) return QSqlTableModel::setData(I,role);
    bool Result = true;
    if (value.isValid()) {
        bool OK;
        int status_id = value.toInt(&OK);
        if (!OK){
            qWarning() << "invalid_status" << value ;
            return false;
        } else if (!AllStatus.contains(status_id)) {
            qWarning() << "Invalid status" << value;
            return false;
        }
        Result |= QSqlTableModel::setData(index(I.row(),9),value,role);
        Result |= QSqlTableModel::setData(I,AllStatus[status_id],role);
    } else {
        Result =  QSqlTableModel::setData(index(I.row(),9), QVariant(), role);
        Result =  QSqlTableModel::setData(I, QString(), role);
    }
    return Result;
}



void Model::cat_item_selected(QVariant Id){
       fCatId = Id;
       adjust_query();

}

void Model::apply_filter(QObject *F){
    fAuthor = F->property("author");
    fTitle = F->property("title");
    fYear = F->property("year");
    adjust_query();
}

void Model::adjust_query(){
    QString QueryText = "select            \n"
                    "b.iid,            \n"
                    "b.rid_catalogue,  \n"
                    "b.author,         \n"
                    "b.title,          \n"
                    "b.eyear,          \n"
                    "b.location,       \n"
                    "b.publisher,      \n"
                    "b.pages,          \n"
                    "b.annote,         \n"
                    "b.rid_status,      \n"
                    "s.title, \n"
                    "b.acomment          \n"
                    "from books b      \n"
                    "left outer join status s \n"
                    "on b.rid_status = s.iid      \n"
                    "where b.rid_catalogue = :CID \n";
     if (fAuthor.isValid()) QueryText += "and b.author ~ :AUTHOR \n";
     if (fTitle.isValid()) QueryText += "and b.title ~ :TITLE \n";
     if (fYear.isValid()) QueryText += "and b.eyear = :YEAR \n";
     QueryText += "; \n";

     QSqlQuery qry;
     qry.prepare(QueryText);
     qry.bindValue(":CID", fCatId);
     if (fAuthor.isValid()) qry.bindValue(":AUTHOR","^"+fAuthor.toString());
     if (fTitle.isValid()) qry.bindValue(":TITLE",fTitle);
     if (fYear.isValid()) qry.bindValue(":YEAR",fYear);
     if ( !qry.exec() ) {
         qCritical() <<  qry.lastError().databaseText().toUtf8().data();
     }
     setQuery(qry);
}

Model::~Model(){

}

View::View(QWidget *parent)
    :QTableView(parent){

    //Model *M = new Model(this);
    Model_EditOnServer *M = new Model_EditOnServer(this);
    setModel(M);

    setColumnHidden(0,true);
    setColumnHidden(1,true);
    setColumnHidden(9,true);

    //запретить длинному тексту складываться в столбик
    setWordWrap(false);
     //строчки разбивать попеременно цветои=м
    setAlternatingRowColors(true);


    {//изменение порядка определения размера строчек,
        //строчки теперь будут подбираться под контент
        QHeaderView *H = verticalHeader();
        H->setSectionResizeMode(QHeaderView::ResizeToContents);
    }{
        QHeaderView *H = horizontalHeader();
        H->setSectionResizeMode(QHeaderView::ResizeToContents);//колонки побирать горизонтальный размеру
        H->setSectionResizeMode(3, QHeaderView::Stretch);//3ю колонку растянуть
    }

    //акшены выставим просто на представлении
    addActions(M->AllActions);
    setContextMenuPolicy(Qt::ActionsContextMenu);

    //установка делегата
    setItemDelegateForColumn(10, new StatusDelegate(this, M->AllStatus));
}

View::~View(){

}



}//namespace Books
}//namespace STORE
