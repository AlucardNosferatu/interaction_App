/****************************************************************************
** Meta object code from reading C++ file 'recognizor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../imu/recognizor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recognizor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Recognizor_t {
    QByteArrayData data[14];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Recognizor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Recognizor_t qt_meta_stringdata_Recognizor = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Recognizor"
QT_MOC_LITERAL(1, 11, 10), // "newEMGData"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 6), // "float*"
QT_MOC_LITERAL(4, 30, 7), // "emgdata"
QT_MOC_LITERAL(5, 38, 9), // "datacount"
QT_MOC_LITERAL(6, 48, 8), // "newaccel"
QT_MOC_LITERAL(7, 57, 5), // "accel"
QT_MOC_LITERAL(8, 63, 10), // "newIMUData"
QT_MOC_LITERAL(9, 74, 6), // "angles"
QT_MOC_LITERAL(10, 81, 10), // "newGesture"
QT_MOC_LITERAL(11, 92, 7), // "gesture"
QT_MOC_LITERAL(12, 100, 13), // "changeToGrasp"
QT_MOC_LITERAL(13, 114, 6) // "update"

    },
    "Recognizor\0newEMGData\0\0float*\0emgdata\0"
    "datacount\0newaccel\0accel\0newIMUData\0"
    "angles\0newGesture\0gesture\0changeToGrasp\0"
    "update"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Recognizor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       6,    2,   49,    2, 0x06 /* Public */,
       8,    2,   54,    2, 0x06 /* Public */,
      10,    1,   59,    2, 0x06 /* Public */,
      12,    0,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    7,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    9,    5,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Int,

       0        // eod
};

void Recognizor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Recognizor *_t = static_cast<Recognizor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newEMGData((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->newaccel((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->newIMUData((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->newGesture((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->changeToGrasp(); break;
        case 5: { int _r = _t->update();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Recognizor::*_t)(float * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Recognizor::newEMGData)) {
                *result = 0;
            }
        }
        {
            typedef void (Recognizor::*_t)(float * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Recognizor::newaccel)) {
                *result = 1;
            }
        }
        {
            typedef void (Recognizor::*_t)(float * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Recognizor::newIMUData)) {
                *result = 2;
            }
        }
        {
            typedef void (Recognizor::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Recognizor::newGesture)) {
                *result = 3;
            }
        }
        {
            typedef void (Recognizor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Recognizor::changeToGrasp)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject Recognizor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Recognizor.data,
      qt_meta_data_Recognizor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Recognizor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Recognizor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Recognizor.stringdata0))
        return static_cast<void*>(const_cast< Recognizor*>(this));
    return QObject::qt_metacast(_clname);
}

int Recognizor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Recognizor::newEMGData(float * _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Recognizor::newaccel(float * _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Recognizor::newIMUData(float * _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Recognizor::newGesture(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Recognizor::changeToGrasp()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
