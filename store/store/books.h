#ifndef BOOKS_H
#define BOOKS_H

#include <QTableView>
#include <QSqlQueryModel>

namespace STORE {
namespace Books {

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

class View : public QTableView {

    Q_OBJECT

public:
    View(QWidget *parent=0);
    virtual ~View();

};

}//namespace Books
}//namespace STORE

#endif // BOOKS_H
