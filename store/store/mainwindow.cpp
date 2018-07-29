#include "mainwindow.h"
#include "catalogue.h"


namespace STORE {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    Catalogue::TableView *M = new Catalogue::TableView(this);
    setCentralWidget(M);
}

MainWindow::~MainWindow()
{

}


}//namespace STORE
