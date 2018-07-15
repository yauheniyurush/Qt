#include "mainwindow.h"

#include <QMenuBar>
#include <QPushButton>
#include <QToolButton>
#include <QAction>
#include <QTextEdit>
#include <QToolBar>
#include <QDockWidget>
#include <QFrame>
#include <QIcon>
#include <QDebug>

#include "itemeditdialog.h"
#include "table.h"
#include "edit.h"
#include "example1.h"

namespace BIBLIO {

/**
 * @brief MainWindow::MainWindow
 * @param parent
 * Файл с реализацией класса главного окна.
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //qDebug()<<"Hello World";
    QActionGroup *agModes = new QActionGroup(this);
    agModes->setExclusive(true);
    //действие пользователя программируется через QAction
    //для того чтобы можно было действие запретить и тогда
    //все кнопки ведущие к этому действию блокирнуться тоже
    {
        QAction *A = actNewItem = new QAction( this ) ;
        A->setText( tr("Item"));
        connect(A, SIGNAL(triggered()), this,
                   SLOT(newItem())) ;
    } {
        QAction *A = actTableMode = new QAction( this ) ;
        QIcon Ic(":/icons/table");//создание иконки
        A->setText( tr("Table Mode"));
        A->setCheckable(true);
        A->setIcon(Ic);//присабачивание иконки к action
        agModes->addAction(A);
        modeActions.insert("Table",A);
        connect(A, SIGNAL(triggered()), this,
                   SLOT(tableMode())) ;
    }{
        QAction *A = actEditMode = new QAction( this ) ;
        A->setText( tr("Edit mode"));
        A->setCheckable(true);
        agModes->addAction(A);
        modeActions.insert("Edit",A);
        connect(A, SIGNAL(triggered()), this,
                   SLOT(editMode())) ;
    }


    //блокировка действия
    //actNewItem->setEnabled(false);

    //возвращает указатель на меню (создаёт если не создан)
    QMenu *mItem = menuBar()->addMenu(tr("Item (A)")) ;
    mItem->addAction(actNewItem);

    QMenu *mModes = menuBar()->addMenu(tr("Modes")) ;
    mModes->addAction(actTableMode);
    mModes->addAction(actEditMode);

    QToolBar *tbModes = new QToolBar(this);
    tbModes->setWindowTitle(tr("Modes"));
    tbModes->addAction(actTableMode);
    //insertToolBarBreak(tbModes);
    tbModes->addAction(actEditMode);
    addToolBar(Qt::TopToolBarArea,tbModes);

    QToolBar *tbEmpty = new QToolBar(this);
    tbEmpty->setWindowTitle(tr("Empty"));
    addToolBar(Qt::TopToolBarArea,tbEmpty);

    //кнопка
    //QToolButton *B = new QToolButton(this) ;
    //B->setText(tr("Item (B)")) ;
    //B->move(100,100);
    //B->setDefaultAction( actNewItem );

    //ДОБАВЛЯЕМ ТЕКСТОВЫЙ РЕДАКТОР в центральное окно
    //Edit *T = new Edit(this);
    //setCentralWidget(T);
    //editMode();
    tableMode();

    //несколько тестовых припаркованных окон
    QMenu *mWindows = menuBar()->addMenu(tr("Windows"));//в меню добавляем
    {
    QDockWidget *D1 = new QDockWidget(this);
    D1->setWindowTitle(tr("Yellow"));
    QFrame *F1 = new QFrame(this);
    F1->setStyleSheet("background: yellow");//этой функцией можно настраивать вид виджетов
    D1->setWidget(F1);
    addDockWidget(Qt::LeftDockWidgetArea,D1);

    mWindows->addAction(D1->toggleViewAction());//добавляем в меню Windows возможность
                                //включения выключения созданного припаркованного окна
    }{
    QDockWidget *D1 = new QDockWidget(this);
    D1->setWindowTitle(tr("Green"));
    QFrame *F1 = new QFrame(this);
    F1->setStyleSheet("background: green");
    D1->setWidget(F1);
    addDockWidget(Qt::LeftDockWidgetArea,D1);

    mWindows->addAction(D1->toggleViewAction());
    }{
    QDockWidget *D1 = new QDockWidget(this);
    D1->setWindowTitle(tr("Red"));
    QFrame *F1 = new QFrame(this);
    F1->setStyleSheet("background: red");
    D1->setWidget(F1);
    addDockWidget(Qt::LeftDockWidgetArea,D1);

    mWindows->addAction(D1->toggleViewAction());
    }


}

MainWindow::~MainWindow()
{

}

void MainWindow::newItem()
{
    //example1 Dia(this);
    ItemEditDialog Dia (this) ;
    Dia.exec();
}

void MainWindow::tableMode() {
    QWidget *W = centralWidget();
    //проверяем надо ли вообще переключать режим
    if (dynamic_cast<Table*>(W)) return;
    if (W) {
    //проверяем можно ли выключить старый режим
    bool OK = true;
    cancelMode(&OK);
    if (!OK) {
        QString modeName = W->property("modeName").toString();
        QAction *A = modeActions.value(modeName,0);
        if (A) A->setChecked(true);
        return;
    }
    //выключаем старый режим
    setCentralWidget(0);//снимаем центральный виджет
    delete W;
    }
    //включаем новый режим
    W = new Table(this);
    setCentralWidget(W);//ставим новый центральный виджет
    actTableMode->setChecked(true);
}

void MainWindow::editMode(void) {
    QWidget *W = centralWidget();
    //проверяем надо ли вообще переключать режим
    if (dynamic_cast<Edit*>(W)) return;

    if (W) {
    //проверяем можно ли выключить старый режим
    bool OK = true;
    cancelMode(&OK);
    if (!OK) {
        QString modeName = W->property("modeName").toString();
        QAction *A = modeActions.value(modeName,0);
        if (A) A->setChecked(true);
        return;
    }
    //выключаем старый режим
    setCentralWidget(0);//снимаем центральный виджет
    delete W;
    }
    //включаем новый режим
    W = new Edit(this);
    setCentralWidget(W);
    connect(this,SIGNAL(cancelMode(bool*)),W,SLOT(onCancelMode(bool *)));
    actEditMode->setChecked(true);
}


}//BIBLIO
