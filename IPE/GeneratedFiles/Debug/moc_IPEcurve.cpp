/****************************************************************************
** Meta object code from reading C++ file 'IPEcurve.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../IPEcurve.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IPEcurve.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_IPEcurve_t {
    QByteArrayData data[9];
    char stringdata[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_IPEcurve_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_IPEcurve_t qt_meta_stringdata_IPEcurve = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 13),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 6),
QT_MOC_LITERAL(4, 31, 13),
QT_MOC_LITERAL(5, 45, 13),
QT_MOC_LITERAL(6, 59, 13),
QT_MOC_LITERAL(7, 73, 8),
QT_MOC_LITERAL(8, 82, 10)
    },
    "IPEcurve\0p1CheckToggle\0\0option\0"
    "p2CheckToggle\0p3CheckToggle\0p4CheckToggle\0"
    "modified\0applyCurve\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IPEcurve[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08,
       4,    1,   47,    2, 0x08,
       5,    1,   50,    2, 0x08,
       6,    1,   53,    2, 0x08,
       7,    0,   56,    2, 0x08,
       8,    0,   57,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IPEcurve::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IPEcurve *_t = static_cast<IPEcurve *>(_o);
        switch (_id) {
        case 0: _t->p1CheckToggle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->p2CheckToggle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->p3CheckToggle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->p4CheckToggle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->modified(); break;
        case 5: _t->applyCurve(); break;
        default: ;
        }
    }
}

const QMetaObject IPEcurve::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_IPEcurve.data,
      qt_meta_data_IPEcurve,  qt_static_metacall, 0, 0}
};


const QMetaObject *IPEcurve::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IPEcurve::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IPEcurve.stringdata))
        return static_cast<void*>(const_cast< IPEcurve*>(this));
    return QDialog::qt_metacast(_clname);
}

int IPEcurve::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
