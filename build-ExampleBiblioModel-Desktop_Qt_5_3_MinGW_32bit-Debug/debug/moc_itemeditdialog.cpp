/****************************************************************************
** Meta object code from reading C++ file 'itemeditdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ExampleBiblioModel/itemeditdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'itemeditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BIBLIO__IED_HELPER__Buttons_t {
    QByteArrayData data[4];
    char stringdata[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BIBLIO__IED_HELPER__Buttons_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BIBLIO__IED_HELPER__Buttons_t qt_meta_stringdata_BIBLIO__IED_HELPER__Buttons = {
    {
QT_MOC_LITERAL(0, 0, 27),
QT_MOC_LITERAL(1, 28, 9),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 9)
    },
    "BIBLIO::IED_HELPER::Buttons\0accepting\0"
    "\0rejecting"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BIBLIO__IED_HELPER__Buttons[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BIBLIO::IED_HELPER::Buttons::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Buttons *_t = static_cast<Buttons *>(_o);
        switch (_id) {
        case 0: _t->accepting(); break;
        case 1: _t->rejecting(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Buttons::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Buttons::accepting)) {
                *result = 0;
            }
        }
        {
            typedef void (Buttons::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Buttons::rejecting)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject BIBLIO::IED_HELPER::Buttons::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_BIBLIO__IED_HELPER__Buttons.data,
      qt_meta_data_BIBLIO__IED_HELPER__Buttons,  qt_static_metacall, 0, 0}
};


const QMetaObject *BIBLIO::IED_HELPER::Buttons::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BIBLIO::IED_HELPER::Buttons::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BIBLIO__IED_HELPER__Buttons.stringdata))
        return static_cast<void*>(const_cast< Buttons*>(this));
    return QFrame::qt_metacast(_clname);
}

int BIBLIO::IED_HELPER::Buttons::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void BIBLIO::IED_HELPER::Buttons::accepting()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void BIBLIO::IED_HELPER::Buttons::rejecting()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
struct qt_meta_stringdata_BIBLIO__ItemEditDialog_t {
    QByteArrayData data[1];
    char stringdata[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BIBLIO__ItemEditDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BIBLIO__ItemEditDialog_t qt_meta_stringdata_BIBLIO__ItemEditDialog = {
    {
QT_MOC_LITERAL(0, 0, 22)
    },
    "BIBLIO::ItemEditDialog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BIBLIO__ItemEditDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void BIBLIO::ItemEditDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject BIBLIO::ItemEditDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BIBLIO__ItemEditDialog.data,
      qt_meta_data_BIBLIO__ItemEditDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *BIBLIO::ItemEditDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BIBLIO::ItemEditDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BIBLIO__ItemEditDialog.stringdata))
        return static_cast<void*>(const_cast< ItemEditDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int BIBLIO::ItemEditDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE