#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <QAbstractItemModel>
#include <QTableView>
#include <QTreeView>
#include <QColumnView>



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
    virtual QVariant dataBackground(const QModelIndex &I) const;//отвечает за фон строки
    //virtual Item::Data * dataDataBlock(const QModelIndex &I) const;

    //функция для генерации id для динамического свойства новых строк
    int tempId() const {return ++LastTempId;}

public:
    Model(QObject *parent = 0);
    virtual ~  Model();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex & ) const;
    QVariant data(const QModelIndex &I, int role) const ;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &I) const;

private:
    //удаление
    bool delete_all_from_db(Item::Data *D = 0);//удаление из базы
    bool delete_all_from_model(Item::Data *D = 0);//удаление из модели
    //сохранение изменений
    bool save_all_to_db(Item::Data *D=0);//сохраняем изменения
    bool drop_change_mark(Item::Data *D=0);//удаляем флаг что элемент менялся
    bool insert_all_to_db(Item::Data *D=0);//сохраняем новые элементы
    bool adjust_id_for_new(Item::Data *D=0);//сохраняем новые элементы

protected:
    bool delete_all(); //основная функция удаления
    bool save_all();   //основная функция сохранения
    bool insert_all(); //основная функция добавления

public slots:
    void editItem(const QModelIndex &I      , QWidget *parent=0);
    void newItem (const QModelIndex &parentI, QWidget *parent=0);
    void delItem (const QModelIndex &I      , QWidget *parent=0);
    void save();
};

/****************************************************************************/

class TableView : public QTableView {

    Q_OBJECT

private:
    PosAction *actEditItem; //вызов окна редактирования для выбранной строки
    PosAction *actNewItem ;
    PosAction *actDelItem ;
    //Экшены actRootItem и actParentRootItem - для отображения древовидной структуры
    PosAction *actRootItem ;
    QAction   *actParentRootItem ;
    QAction   *actSave;//экшн по сохранению

public:
    TableView(QWidget *parent=0, Model *xModel=0);
    virtual ~ TableView();


private slots:
    void contextMenuRequested(const QPoint &p) ; //контекстное меню
//  void editItem(); //вызов окна редактирования для выбранной строки    
    //Сигналы showChildren и showParent - для отображения древовидной структуры
    void showChildren(const QModelIndex &I, QWidget *);
    void showParent(void);

//signals:
//  void mustEditItem(const QModelIndex &I, QWidget *parent);

};

/****************************************************************************/
//класс для реализации древовидного представления
class TreeView : public QTreeView {

    Q_OBJECT

public:
    TreeView(QWidget *parent=0, Model *xModel=0);
    virtual ~TreeView();

};

/****************************************************************************/
//класс для реализации колоночного представления
class ColumnView : public QColumnView {

    Q_OBJECT

public:
    ColumnView(QWidget *parent=0, Model *xModel=0);
    virtual ~ColumnView();

};
/****************************************************************************/
}//Catalogue
}//namespace STORE

#endif // CATALOGUE_H
