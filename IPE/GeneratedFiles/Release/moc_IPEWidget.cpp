/****************************************************************************
** Meta object code from reading C++ file 'IPEWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../IPEWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IPEWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_IPEWidget_t {
    QByteArrayData data[8];
    char stringdata[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_IPEWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_IPEWidget_t qt_meta_stringdata_IPEWidget = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 18),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 19),
QT_MOC_LITERAL(4, 50, 15),
QT_MOC_LITERAL(5, 66, 13),
QT_MOC_LITERAL(6, 80, 13),
QT_MOC_LITERAL(7, 94, 13)
    },
    "IPEWidget\0setSelectionStatus\0\0"
    "setMoveCanvasStatus\0setRotateStatus\0"
    "setZoomStatus\0cameraRotateL\0cameraRotateR\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IPEWidget[] = {

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
       1,    0,   44,    2, 0x08,
       3,    0,   45,    2, 0x08,
       4,    0,   46,    2, 0x08,
       5,    0,   47,    2, 0x08,
       6,    0,   48,    2, 0x08,
       7,    0,   49,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IPEWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IPEWidget *_t = static_cast<IPEWidget *>(_o);
        switch (_id) {
        case 0: _t->setSelectionStatus(); break;
        case 1: _t->setMoveCanvasStatus(); break;
        case 2: _t->setRotateStatus(); break;
        case 3: _t->setZoomStatus(); break;
        case 4: _t->cameraRotateL(); break;
        case 5: _t->cameraRotateR(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject IPEWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_IPEWidget.data,
      qt_meta_data_IPEWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *IPEWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IPEWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IPEWidget.stringdata))
        return static_cast<void*>(const_cast< IPEWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int IPEWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
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
