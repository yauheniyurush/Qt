#include "catitemedit.h"

namespace STORE {
namespace Catalogue {
namespace Item {

Frame::Frame(QWidget *parent) :QFrame(parent){

    ui.setupUi(this);

}

Frame::~Frame(){

}

/** Тут сделать нормальную проверку данных */
void Frame::is_good(bool *pOK){
    *pOK = true;
}


Dialog::Dialog(QWidget *parent)
    : CommonDialog(parent) {
    {
        Frame *F = pFrame = new Frame(this);
        setCentralFrame(F);
    }
}

Dialog::~Dialog(){

}

}//namespace Item
}//namespace Catalogue
}//namespace STORE
