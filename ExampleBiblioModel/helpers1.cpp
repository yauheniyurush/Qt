#include "helpers.h"
#include <QWidget>
#include <QSizePolicy>

namespace BIBLIO {

namespace hlp {

void setHorPolicy(QWidget *W, QSizePolicy::Policy Pol)
{
    QSizePolicy P = W->sizePolicy();
    P.setHorizontalPolicy(Pol);
    W->setSizePolicy(P);
}

void setWidth(QWidget *W, int width)
{
    QSize s = W->maximumSize();
    s.setWidth(width);
    W->setMaximumSize(s);
}

}//namespace hlp

}//namespace BIBLIO
//17:42 d3-3
