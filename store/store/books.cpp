#include "books.h"
#include <QtSql>
#include <QtDebug>
#include <QHeaderView>

namespace STORE {
namespace Books {


Model::Model(QObject *parent)
    :QSqlQueryModel(parent) {


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

    Model *M = new Model(this);
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
    }

}

View::~View(){

}

}//namespace Books
}//namespace STORE
