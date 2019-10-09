/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../windows/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[48];
    char stringdata0[889];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 8), // "updateUI"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 22), // "on_freshButton_clicked"
QT_MOC_LITERAL(4, 44, 22), // "on_onEMGButton_clicked"
QT_MOC_LITERAL(5, 67, 22), // "on_beginButton_clicked"
QT_MOC_LITERAL(6, 90, 21), // "on_stopButton_clicked"
QT_MOC_LITERAL(7, 112, 22), // "on_ResetButton_clicked"
QT_MOC_LITERAL(8, 135, 22), // "on_clearButton_clicked"
QT_MOC_LITERAL(9, 158, 21), // "on_saveButton_clicked"
QT_MOC_LITERAL(10, 180, 21), // "on_initButton_clicked"
QT_MOC_LITERAL(11, 202, 24), // "on_pushButtonRLD_clicked"
QT_MOC_LITERAL(12, 227, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(13, 251, 22), // "on_noiseButton_clicked"
QT_MOC_LITERAL(14, 274, 26), // "on_normalMeaButton_clicked"
QT_MOC_LITERAL(15, 301, 17), // "addDatatoEMGPlots"
QT_MOC_LITERAL(16, 319, 6), // "float*"
QT_MOC_LITERAL(17, 326, 7), // "emgdata"
QT_MOC_LITERAL(18, 334, 11), // "n_datacount"
QT_MOC_LITERAL(19, 346, 17), // "addDatatoIMUPlots"
QT_MOC_LITERAL(20, 364, 6), // "angles"
QT_MOC_LITERAL(21, 371, 19), // "addDatatoaccelPlots"
QT_MOC_LITERAL(22, 391, 5), // "accel"
QT_MOC_LITERAL(23, 397, 16), // "responseReceived"
QT_MOC_LITERAL(24, 414, 3), // "res"
QT_MOC_LITERAL(25, 418, 11), // "showGesture"
QT_MOC_LITERAL(26, 430, 7), // "gesture"
QT_MOC_LITERAL(27, 438, 12), // "clearGesture"
QT_MOC_LITERAL(28, 451, 22), // "on_onIMUButton_clicked"
QT_MOC_LITERAL(29, 474, 21), // "on_loadButton_clicked"
QT_MOC_LITERAL(30, 496, 24), // "on_Slider_sliderReleased"
QT_MOC_LITERAL(31, 521, 21), // "on_playButton_clicked"
QT_MOC_LITERAL(32, 543, 23), // "on_editorButton_clicked"
QT_MOC_LITERAL(33, 567, 22), // "on_pauseButton_clicked"
QT_MOC_LITERAL(34, 590, 27), // "on_squaretestButton_clicked"
QT_MOC_LITERAL(35, 618, 20), // "on_fb1Button_clicked"
QT_MOC_LITERAL(36, 639, 20), // "on_fb2Button_clicked"
QT_MOC_LITERAL(37, 660, 20), // "on_fb3Button_clicked"
QT_MOC_LITERAL(38, 681, 20), // "on_fb4Button_clicked"
QT_MOC_LITERAL(39, 702, 20), // "on_fb5Button_clicked"
QT_MOC_LITERAL(40, 723, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(41, 745, 24), // "on_onRobotButton_clicked"
QT_MOC_LITERAL(42, 770, 22), // "on_radioButton_toggled"
QT_MOC_LITERAL(43, 793, 7), // "checked"
QT_MOC_LITERAL(44, 801, 24), // "on_radioButton_2_toggled"
QT_MOC_LITERAL(45, 826, 23), // "on_play3XButton_clicked"
QT_MOC_LITERAL(46, 850, 21), // "on_stepButton_clicked"
QT_MOC_LITERAL(47, 872, 16) // "checkRadioButton"

    },
    "MainWindow\0updateUI\0\0on_freshButton_clicked\0"
    "on_onEMGButton_clicked\0on_beginButton_clicked\0"
    "on_stopButton_clicked\0on_ResetButton_clicked\0"
    "on_clearButton_clicked\0on_saveButton_clicked\0"
    "on_initButton_clicked\0on_pushButtonRLD_clicked\0"
    "on_pushButton_2_clicked\0on_noiseButton_clicked\0"
    "on_normalMeaButton_clicked\0addDatatoEMGPlots\0"
    "float*\0emgdata\0n_datacount\0addDatatoIMUPlots\0"
    "angles\0addDatatoaccelPlots\0accel\0"
    "responseReceived\0res\0showGesture\0"
    "gesture\0clearGesture\0on_onIMUButton_clicked\0"
    "on_loadButton_clicked\0on_Slider_sliderReleased\0"
    "on_playButton_clicked\0on_editorButton_clicked\0"
    "on_pauseButton_clicked\0"
    "on_squaretestButton_clicked\0"
    "on_fb1Button_clicked\0on_fb2Button_clicked\0"
    "on_fb3Button_clicked\0on_fb4Button_clicked\0"
    "on_fb5Button_clicked\0on_pushButton_clicked\0"
    "on_onRobotButton_clicked\0"
    "on_radioButton_toggled\0checked\0"
    "on_radioButton_2_toggled\0"
    "on_play3XButton_clicked\0on_stepButton_clicked\0"
    "checkRadioButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  204,    2, 0x08 /* Private */,
       3,    0,  205,    2, 0x08 /* Private */,
       4,    0,  206,    2, 0x08 /* Private */,
       5,    0,  207,    2, 0x08 /* Private */,
       6,    0,  208,    2, 0x08 /* Private */,
       7,    0,  209,    2, 0x08 /* Private */,
       8,    0,  210,    2, 0x08 /* Private */,
       9,    0,  211,    2, 0x08 /* Private */,
      10,    0,  212,    2, 0x08 /* Private */,
      11,    0,  213,    2, 0x08 /* Private */,
      12,    0,  214,    2, 0x08 /* Private */,
      13,    0,  215,    2, 0x08 /* Private */,
      14,    0,  216,    2, 0x08 /* Private */,
      15,    2,  217,    2, 0x08 /* Private */,
      19,    2,  222,    2, 0x08 /* Private */,
      21,    2,  227,    2, 0x08 /* Private */,
      23,    1,  232,    2, 0x08 /* Private */,
      25,    1,  235,    2, 0x08 /* Private */,
      27,    0,  238,    2, 0x08 /* Private */,
      28,    0,  239,    2, 0x08 /* Private */,
      29,    0,  240,    2, 0x08 /* Private */,
      30,    0,  241,    2, 0x08 /* Private */,
      31,    0,  242,    2, 0x08 /* Private */,
      32,    0,  243,    2, 0x08 /* Private */,
      33,    0,  244,    2, 0x08 /* Private */,
      34,    0,  245,    2, 0x08 /* Private */,
      35,    0,  246,    2, 0x08 /* Private */,
      36,    0,  247,    2, 0x08 /* Private */,
      37,    0,  248,    2, 0x08 /* Private */,
      38,    0,  249,    2, 0x08 /* Private */,
      39,    0,  250,    2, 0x08 /* Private */,
      40,    0,  251,    2, 0x08 /* Private */,
      41,    0,  252,    2, 0x08 /* Private */,
      42,    1,  253,    2, 0x08 /* Private */,
      44,    1,  256,    2, 0x08 /* Private */,
      45,    0,  259,    2, 0x08 /* Private */,
      46,    0,  260,    2, 0x08 /* Private */,
      47,    0,  261,    2, 0x08 /* Private */,

 // slots: parameters
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
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,   17,   18,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,   20,   18,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,   22,   18,
    QMetaType::Void, QMetaType::UChar,   24,
    QMetaType::Void, QMetaType::QString,   26,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   43,
    QMetaType::Void, QMetaType::Bool,   43,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateUI(); break;
        case 1: _t->on_freshButton_clicked(); break;
        case 2: _t->on_onEMGButton_clicked(); break;
        case 3: _t->on_beginButton_clicked(); break;
        case 4: _t->on_stopButton_clicked(); break;
        case 5: _t->on_ResetButton_clicked(); break;
        case 6: _t->on_clearButton_clicked(); break;
        case 7: _t->on_saveButton_clicked(); break;
        case 8: _t->on_initButton_clicked(); break;
        case 9: _t->on_pushButtonRLD_clicked(); break;
        case 10: _t->on_pushButton_2_clicked(); break;
        case 11: _t->on_noiseButton_clicked(); break;
        case 12: _t->on_normalMeaButton_clicked(); break;
        case 13: _t->addDatatoEMGPlots((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->addDatatoIMUPlots((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->addDatatoaccelPlots((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 16: _t->responseReceived((*reinterpret_cast< unsigned char(*)>(_a[1]))); break;
        case 17: _t->showGesture((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->clearGesture(); break;
        case 19: _t->on_onIMUButton_clicked(); break;
        case 20: _t->on_loadButton_clicked(); break;
        case 21: _t->on_Slider_sliderReleased(); break;
        case 22: _t->on_playButton_clicked(); break;
        case 23: _t->on_editorButton_clicked(); break;
        case 24: _t->on_pauseButton_clicked(); break;
        case 25: _t->on_squaretestButton_clicked(); break;
        case 26: _t->on_fb1Button_clicked(); break;
        case 27: _t->on_fb2Button_clicked(); break;
        case 28: _t->on_fb3Button_clicked(); break;
        case 29: _t->on_fb4Button_clicked(); break;
        case 30: _t->on_fb5Button_clicked(); break;
        case 31: _t->on_pushButton_clicked(); break;
        case 32: _t->on_onRobotButton_clicked(); break;
        case 33: _t->on_radioButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->on_radioButton_2_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->on_play3XButton_clicked(); break;
        case 36: _t->on_stepButton_clicked(); break;
        case 37: _t->checkRadioButton(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 38)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 38;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
