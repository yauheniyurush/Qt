#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <QAbstractItemModel>
#include <QTableView>
#include "catitemedit.h"

class QAction;

namespace STORE {
    class PosAction;
}

namespace STORE {
namespace Catalogue {

/****************************************************************************/
class Model: public QAbstractItemModel {

    Q_OBJECT

private:
    mutable int LastTempId; // идентификатор последнего id сгенерированного функцией tempId
    Item::List Cat;

protected:
    virtual QVariant dataDisplay(const QModelIndex &I) const;
    virtual QVariant dataTextAlignment(const QModelIndex &I) const;
    virtual QVariant dataForeground(const QModelIndex &I) const;
    virtual QVariant dataFont(const QModelIndex &I) const;
    virtual QVariant dataToolTip(const QModelIndex &I) const;
    //virtual Item::Data * dataDataBlock(const QModelIndex &I) const;

    //функция для генерации id для динамического свойства новых строк
    int tempId() const {return ++LastTempId;}

public:
    Model(QObject *parent = 0);
    virtual ~  Model();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &I, int role) const ;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &I) const;

public slots:
    void editItem(const QModelIndex &I      , QWidget *parent=0);
    void newItem (const QModelIndex &parentI, QWidget *parent=0);
    void delItem (const QModelIndex &I      , QWidget *parent=0);

};

/****************************************************************************/

class TableView : public QTableView {

    Q_OBJECT

private:
    PosAction *actEditItem; //вызов окна редактирования для выбранной строки
    PosAction *actNewItem ;
    PosAction *actDelItem ;

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
