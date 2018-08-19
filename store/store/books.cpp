#include "books.h"

namespace STORE {
namespace Books {


Model::Model(QObject *parent)
    :QSqlQueryModel(parent) {

}

Model::~Model(){

}

View::View(QWidget *parent)
    :QTableView(parent){

}

View::~View(){

}

}//namespace Books
}//namespace STORE
