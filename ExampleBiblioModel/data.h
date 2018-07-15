#ifndef DATA_H
#define DATA_H

#include <QString>

namespace BIBLIO {
namespace DATA {

struct Object {
    QString Autor ;
    QString Title;
    QString SubTitle;
    QString Location;
    QString Publisher;
    int Year;
    //Comment

    virtual ~Object() {} ;//деструктор нужен чтобы работал dynamic cast
};

struct Book: public Object {
    int TotalPages;
};

struct Article: public Object {
    QString Journal ;
    QString Volume ;
    QString Issue ;
    QString Pages ;
};

}//namespace DATA


}//namespace BIBLIO
#endif // DATA_H
