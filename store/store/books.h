#ifndef BOOKS_H
#define BOOKS_H

#include <QTableView>
#include <QSqlQueryModel>

namespace STORE {
namespace Books {

class Model : public QSqlQueryModel {

    Q_OBJECT

public:
    Model(QObject *parent=0);
    virtual ~Model();

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
