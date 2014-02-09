/****************************************************************************
** Meta object code from reading C++ file 'ipemain.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ipemain.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ipemain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_IPEMain_t {
    QByteArrayData data[17];
    char stringdata[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_IPEMain_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_IPEMain_t qt_meta_stringdata_IPEMain = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 13),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 13),
QT_MOC_LITERAL(4, 37, 15),
QT_MOC_LITERAL(5, 53, 7),
QT_MOC_LITERAL(6, 61, 8),
QT_MOC_LITERAL(7, 70, 8),
QT_MOC_LITERAL(8, 79, 8),
QT_MOC_LITERAL(9, 88, 8),
QT_MOC_LITERAL(10, 97, 6),
QT_MOC_LITERAL(11, 104, 6),
QT_MOC_LITERAL(12, 111, 6),
QT_MOC_LITERAL(13, 118, 9),
QT_MOC_LITERAL(14, 128, 10),
QT_MOC_LITERAL(15, 139, 8),
QT_MOC_LITERAL(16, 148, 10)
    },
    "IPEMain\0openImageFile\0\0saveImageFile\0"
    "saveAsImageFile\0exitApp\0aboutApp\0"
    "setCurve\0setHisto\0setMatch\0setDFT\0"
    "setAve\0setMed\0setRobert\0setPrewitt\0"
    "setSobel\0setLaplace\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IPEMain[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08,
       3,    0,   90,    2, 0x08,
       4,    0,   91,    2, 0x08,
       5,    0,   92,    2, 0x08,
       6,    0,   93,    2, 0x08,
       7,    0,   94,    2, 0x08,
       8,    0,   95,    2, 0x08,
       9,    0,   96,    2, 0x08,
      10,    0,   97,    2, 0x08,
      11,    0,   98,    2, 0x08,
      12,    0,   99,    2, 0x08,
      13,    0,  100,    2, 0x08,
      14,    0,  101,    2, 0x08,
      15,    0,  102,    2, 0x08,
      16,    0,  103,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IPEMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IPEMain *_t = static_cast<IPEMain *>(_o);
        switch (_id) {
        case 0: _t->openImageFile(); break;
        case 1: { bool _r = _t->saveImageFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->saveAsImageFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->exitApp(); break;
        case 4: _t->aboutApp(); break;
        case 5: _t->setCurve(); break;
        case 6: _t->setHisto(); break;
        case 7: _t->setMatch(); break;
        case 8: _t->setDFT(); break;
        case 9: _t->setAve(); break;
        case 10: _t->setMed(); break;
        case 11: _t->setRobert(); break;
        case 12: _t->setPrewitt(); break;
        case 13: _t->setSobel(); break;
        case 14: _t->setLaplace(); break;
        default: ;
        }
    }
}

const QMetaObject IPEMain::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_IPEMain.data,
      qt_meta_data_IPEMain,  qt_static_metacall, 0, 0}
};


const QMetaObject *IPEMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IPEMain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IPEMain.stringdata))
        return static_cast<void*>(const_cast< IPEMain*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int IPEMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
