#ifndef BOOKS_H
#define BOOKS_H

#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QItemDelegate>

namespace STORE {
namespace Books {

/*****************************************************************/
//класс делегата для редактирования статуса
class StatusDelegate : public QItemDelegate {

    Q_OBJECT

private:
    QMap<int,QString> fAllStatus;

public:
    StatusDelegate(QObject *parent, const QMap<int,QString> &AllStatus);
    virtual ~StatusDelegate(void) {}

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &I) const;
    void setEditorData(QWidget *editor,
                       const QModelIndex &I) const;
    void setModelData(QWidget * editor,
                      QAbstractItemModel *model,
                      const QModelIndex &I) const;
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &I) const;

};

/*****************************************************************/

class Model : public QSqlQueryModel {

    Q_OBJECT

private:
    QVariant fAuthor;
    QVariant fTitle;
    QVariant fYear;
    QVariant fCatId;
    void adjust_query();

public:
    Model(QObject *parent=0);
    virtual ~Model();

    int columnCount(const QModelIndex &parent) const {return 12;}

public slots:
    void cat_item_selected(QVariant Id);
    void apply_filter(QObject *F);

};

class Model_EditOnServer : public QSqlTableModel {

    Q_OBJECT

private:
    QVariant fAuthor;
    QVariant fTitle;
    QVariant fYear;
    QVariant fCatId;
    void adjust_query();


    QAction *actDeleteRow;
    QAction *actNewRow;
    QAction *actSaveAll;//сохранение всех изменений в постоянную таблицу бд (сохраняются только измнененные строки)
    QAction *actRestoreAll;



protected slots:
    void on_save_all();
    void on_restore_all();
    void on_delete_row();
    void on_new_row();

public:
    QMap<int,QString>AllStatus;
    QList<QAction*> AllActions;

public:
    Model_EditOnServer(QObject *parent=0);
    virtual ~Model_EditOnServer();

    int columnCount(const QModelIndex &parent) const {return 12;}
    Qt::ItemFlags flags(const QModelIndex &) const ;
    QVariant data(const QModelIndex &idx, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
public slots:
    void cat_item_selected(QVariant Id);
    void apply_filter(QObject *F);

};

class View : public QTableView {

    Q_OBJECT

public:
    View(QWidget *parent=0);
    virtual ~View();

};

}//namespace Books
}//namespace STORE

#endif // BOOKS_H
