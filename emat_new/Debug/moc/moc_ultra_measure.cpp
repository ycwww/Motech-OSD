/****************************************************************************
** Meta object code from reading C++ file 'ultra_measure.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ultra_measure.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ultra_measure.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ultra_measure_t {
    QByteArrayData data[17];
    char stringdata0[290];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ultra_measure_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ultra_measure_t qt_meta_stringdata_ultra_measure = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ultra_measure"
QT_MOC_LITERAL(1, 14, 25), // "ptn_clicked_connect_slots"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 16), // "ready_read_slots"
QT_MOC_LITERAL(4, 58, 19), // "start_measure_slots"
QT_MOC_LITERAL(5, 78, 19), // "timer_timeout_slots"
QT_MOC_LITERAL(6, 98, 18), // "stop_measure_slots"
QT_MOC_LITERAL(7, 117, 28), // "ptn_clicked_disconnect_slots"
QT_MOC_LITERAL(8, 146, 12), // "data_process"
QT_MOC_LITERAL(9, 159, 22), // "timer_out_get_electric"
QT_MOC_LITERAL(10, 182, 25), // "start_laser_measure_slots"
QT_MOC_LITERAL(11, 208, 18), // "stop_laser_measure"
QT_MOC_LITERAL(12, 227, 16), // "connect_to_laser"
QT_MOC_LITERAL(13, 244, 18), // "display_laser_data"
QT_MOC_LITERAL(14, 263, 4), // "data"
QT_MOC_LITERAL(15, 268, 17), // "display_error_msg"
QT_MOC_LITERAL(16, 286, 3) // "msg"

    },
    "ultra_measure\0ptn_clicked_connect_slots\0"
    "\0ready_read_slots\0start_measure_slots\0"
    "timer_timeout_slots\0stop_measure_slots\0"
    "ptn_clicked_disconnect_slots\0data_process\0"
    "timer_out_get_electric\0start_laser_measure_slots\0"
    "stop_laser_measure\0connect_to_laser\0"
    "display_laser_data\0data\0display_error_msg\0"
    "msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ultra_measure[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    1,   90,    2, 0x08 /* Private */,
      15,    1,   93,    2, 0x08 /* Private */,

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
    QMetaType::Void, QMetaType::Double,   14,
    QMetaType::Void, QMetaType::QString,   16,

       0        // eod
};

void ultra_measure::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ultra_measure *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ptn_clicked_connect_slots(); break;
        case 1: _t->ready_read_slots(); break;
        case 2: _t->start_measure_slots(); break;
        case 3: _t->timer_timeout_slots(); break;
        case 4: _t->stop_measure_slots(); break;
        case 5: _t->ptn_clicked_disconnect_slots(); break;
        case 6: _t->data_process(); break;
        case 7: _t->timer_out_get_electric(); break;
        case 8: _t->start_laser_measure_slots(); break;
        case 9: _t->stop_laser_measure(); break;
        case 10: _t->connect_to_laser(); break;
        case 11: _t->display_laser_data((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->display_error_msg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ultra_measure::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ultra_measure.data,
    qt_meta_data_ultra_measure,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ultra_measure::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ultra_measure::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ultra_measure.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ultra_measure::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
