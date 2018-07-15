#include "bibliomodel.h"

namespace BIBLIO {

BiblioModel::BiblioModel(QObject *parent)
    :QAbstractTableModel(parent) {

    //Временно
    DATA::Book *X = new DATA::Book() ;
    X->Autor = "Vasya Pupkin";
    X->Title = "Hello, world!!!";
    List.append(X);

}

BiblioModel::~BiblioModel(){
    QListIterator<DATA::Object*> it(List) ;
    while (it.hasNext()){
        DATA::Object *X = it.next();
        delete X ;
    }
    //foreach - можно посмотреть
}

int BiblioModel::rowCount   (const QModelIndex & parent) const {
    if (parent.isValid()) return 0;
    return List.size();
}
int BiblioModel::columnCount(const QModelIndex & parent) const{
    if (parent.isValid()) return 0;
    return 2;
}

QVariant BiblioModel::data(const QModelIndex &I, int role ) const{
    if (role == Qt::DisplayRole) {
        switch (I.column() ) {
        case 0:
            return List.at(I.row())->Autor;
        case 1:
            return List.at(I.row())->Title;
        default :
            return QVariant();
        }
    } else {
        return QVariant();
    }
}

}//namespace BIBLIO
