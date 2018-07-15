#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

class QAction ;

/**
 * @brief
 * Файл объявления класса главного окна приложения.
 */

namespace BIBLIO {

class MainWindow : public QMainWindow
{
    Q_OBJECT //ДОБАВЛЯЕМ QOBJECT В КАЖДЫЙ НОВЫЙ КЛАСС

private:
    QAction *actNewItem ;

    QMap<QString,QAction*> modeActions;
    QAction *actEditMode ;
    QAction *actTableMode ;

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

protected slots:
    void newItem(void ) ;//в слотах нельзя использовать параметры по умолчанию, в  отличие от сигналов
    void editMode(void) ;
    void tableMode(void) ;
signals:
    void cancelMode(bool *OK=0);//сигналы возвращают всегда void
};

} // BIBLIO

#endif // MAINWINDOW_H
