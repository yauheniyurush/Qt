#include "mainwindow.h"
#include "catalogue.h"
#include "books.h"

#include <QDockWidget>

namespace STORE {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    Books::View *W = new Books::View(this);
    setCentralWidget(W);

    Catalogue::Model *M = 0;

    {
        QDockWidget *D = new QDockWidget(this);
        D->setWindowTitle(tr("Catalogue"));
        Catalogue::ColumnView *W = new Catalogue::ColumnView(D);
        D->setWidget(W);
        addDockWidget(Qt::TopDockWidgetArea,D);
        M = qobject_cast<Catalogue::Model*>(W->model());
    }
    {
        QDockWidget *D = new QDockWidget(this);
        D->setWindowTitle(tr("Catalogue"));
        D->setWidget(new Catalogue::TreeView(D,M));
        addDockWidget(Qt::LeftDockWidgetArea,D);
    }
}

MainWindow::~MainWindow()
{

}


}//namespace STORE
