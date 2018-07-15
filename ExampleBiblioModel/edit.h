#ifndef EDIT_H
#define EDIT_H

#include<QTextEdit>

namespace BIBLIO {

class Edit : public QTextEdit {

    Q_OBJECT

public:
    Edit(QWidget *parent=0);
    virtual ~Edit();

public slots:
    void onCancelMode(bool *OK);
};


}//namespace BIBLIO {
#endif // EDIT_H
