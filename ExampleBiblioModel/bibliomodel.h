#ifndef BIBLIOMODEL_H
#define BIBLIOMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "data.h"

namespace BIBLIO {


class BiblioModel : public QAbstractTableModel
{

    Q_OBJECT

private:
    QList<DATA::Object*> List ;

public:
    BiblioModel(QObject *parent = 0);
    virtual ~BiblioModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex &I, int role = Qt::DisplayRole) const;

    DATA::Object *at (int k) {return List.at(k) ;}
};


}//namespace BIBLIO

#endif // BIBLIOMODEL_H
