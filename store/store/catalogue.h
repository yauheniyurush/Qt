#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <QAbstractTableModel>
#include <QTableView>
#include "catitemedit.h"

class QAction;

namespace STORE {
    class PosAction;
}

namespace STORE {
namespace Catalogue {

/****************************************************************************/
class Model: public QAbstractTableModel {

    Q_OBJECT

private:
    QList<Item::Data*> Cat;

protected:
    virtual QVariant dataDisplay(const QModelIndex &I) const;
    virtual QVariant dataTextAlignment(const QModelIndex &I) const;
    virtual Item::Data * dataDataBlock(const QModelIndex &I) const;

public:
    Model(QObject *parent = 0);
    virtual ~ Model();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &I, int role) const ;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role) const;

public slots:
    void editItem( const QModelIndex &I, QWidget *parent=0) ;

};

/****************************************************************************/

class TableView : public QTableView {

    Q_OBJECT

private:
    PosAction *actEditItem; //вызов окна редактирования для выбранной строки

public:
    TableView(QWidget *parent=0);
    virtual ~ TableView();


private slots:
    void contextMenuRequested(const QPoint &p) ;
//  void editItem(); //вызов окна редактирования для выбранной строки

//signals:
//  void mustEditItem(const QModelIndex &I, QWidget *parent);

};


/****************************************************************************/
}//Catalogue
}//namespace STORE

#endif // CATALOGUE_H
