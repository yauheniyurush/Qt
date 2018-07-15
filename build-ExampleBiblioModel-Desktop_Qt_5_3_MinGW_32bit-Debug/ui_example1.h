/********************************************************************************
** Form generated from reading UI file 'example1.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMPLE1_H
#define UI_EXAMPLE1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_example1
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *edt;
    QComboBox *cbxCurrent;
    QWidget *layoutWidget;
    QVBoxLayout *layAuthor;
    QLabel *lblAuthor;
    QLineEdit *edtAuthor;
    QFrame *btm;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *hSpcBtn;
    QPushButton *btnOk;
    QPushButton *btnCansel;

    void setupUi(QDialog *example1)
    {
        if (example1->objectName().isEmpty())
            example1->setObjectName(QStringLiteral("example1"));
        example1->resize(400, 300);
        verticalLayout = new QVBoxLayout(example1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        edt = new QFrame(example1);
        edt->setObjectName(QStringLiteral("edt"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edt->sizePolicy().hasHeightForWidth());
        edt->setSizePolicy(sizePolicy);
        edt->setFrameShape(QFrame::StyledPanel);
        edt->setFrameShadow(QFrame::Sunken);
        cbxCurrent = new QComboBox(edt);
        cbxCurrent->setObjectName(QStringLiteral("cbxCurrent"));
        cbxCurrent->setGeometry(QRect(300, 200, 71, 22));
        layoutWidget = new QWidget(edt);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 361, 42));
        layAuthor = new QVBoxLayout(layoutWidget);
        layAuthor->setSpacing(0);
        layAuthor->setObjectName(QStringLiteral("layAuthor"));
        layAuthor->setContentsMargins(0, 0, 0, 0);
        lblAuthor = new QLabel(layoutWidget);
        lblAuthor->setObjectName(QStringLiteral("lblAuthor"));

        layAuthor->addWidget(lblAuthor);

        edtAuthor = new QLineEdit(layoutWidget);
        edtAuthor->setObjectName(QStringLiteral("edtAuthor"));

        layAuthor->addWidget(edtAuthor);

        layAuthor->setStretch(0, 3);
        layAuthor->setStretch(1, 1);

        verticalLayout->addWidget(edt);

        btm = new QFrame(example1);
        btm->setObjectName(QStringLiteral("btm"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btm->sizePolicy().hasHeightForWidth());
        btm->setSizePolicy(sizePolicy1);
        btm->setFrameShape(QFrame::StyledPanel);
        btm->setFrameShadow(QFrame::Sunken);
        horizontalLayout = new QHBoxLayout(btm);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        hSpcBtn = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(hSpcBtn);

        btnOk = new QPushButton(btm);
        btnOk->setObjectName(QStringLiteral("btnOk"));

        horizontalLayout->addWidget(btnOk);

        btnCansel = new QPushButton(btm);
        btnCansel->setObjectName(QStringLiteral("btnCansel"));

        horizontalLayout->addWidget(btnCansel);


        verticalLayout->addWidget(btm);


        retranslateUi(example1);

        QMetaObject::connectSlotsByName(example1);
    } // setupUi

    void retranslateUi(QDialog *example1)
    {
        example1->setWindowTitle(QApplication::translate("example1", "Dialog", 0));
        lblAuthor->setText(QApplication::translate("example1", "Author", 0));
        btnOk->setText(QApplication::translate("example1", "Ok", 0));
        btnCansel->setText(QApplication::translate("example1", "Cansel", 0));
    } // retranslateUi

};

namespace Ui {
    class example1: public Ui_example1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMPLE1_H
