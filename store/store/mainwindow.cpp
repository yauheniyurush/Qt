#include "mainwindow.h"
#include "catalogue.h"
#include "books.h"
#include "filter.h"

#include <QDockWidget>

namespace STORE {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    Books::View *B = new Books::View(this);
    setCentralWidget(B);

    Catalogue::ColumnView *W = 0;
    Filter *F =0;
    {
        QDockWidget *D = new QDockWidget(this);
        D->setWindowTitle(tr("Catalogue"));
        W = new Catalogue::ColumnView(D);
        D->setWidget(W);
        addDockWidget(Qt::TopDockWidgetArea,D);

    }
    {
        QDockWidget *D = new QDockWidget(this);
        D->setWindowTitle(tr("Filter"));
        F= new Filter(D);
        D->setWidget(F);
        addDockWidget(Qt::LeftDockWidgetArea,D);
    }

    connect(W,SIGNAL(item_selected(QVariant)),
            B->model(),SLOT(cat_item_selected(QVariant)));

    connect(F,SIGNAL(apply_filter(QObject*)),
            B->model(),SLOT(apply_filter(QObject*)));
}

MainWindow::~MainWindow()
{

}


}//namespace STORE
