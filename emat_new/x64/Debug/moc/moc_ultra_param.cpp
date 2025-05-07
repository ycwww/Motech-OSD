/****************************************************************************
** Meta object code from reading C++ file 'ultra_param.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ultra_param.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ultra_param.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ultra_param_t {
    QByteArrayData data[12];
    char stringdata0[265];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ultra_param_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ultra_param_t qt_meta_stringdata_ultra_param = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ultra_param"
QT_MOC_LITERAL(1, 12, 28), // "ptn_clicked_disconnect_slots"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 25), // "ptn_clicked_connect_slots"
QT_MOC_LITERAL(4, 68, 16), // "ready_read_slots"
QT_MOC_LITERAL(5, 85, 28), // "ptn_clicked_send_param_slots"
QT_MOC_LITERAL(6, 114, 28), // "ptn_clicked_read_param_slots"
QT_MOC_LITERAL(7, 143, 31), // "ptn_clicked_send_ex_param_slots"
QT_MOC_LITERAL(8, 175, 25), // "ptn_start_thickness_slots"
QT_MOC_LITERAL(9, 201, 24), // "ptn_stop_thickness_slots"
QT_MOC_LITERAL(10, 226, 18), // "ptn_wave_get_slots"
QT_MOC_LITERAL(11, 245, 19) // "timer_timeout_slots"

    },
    "ultra_param\0ptn_clicked_disconnect_slots\0"
    "\0ptn_clicked_connect_slots\0ready_read_slots\0"
    "ptn_clicked_send_param_slots\0"
    "ptn_clicked_read_param_slots\0"
    "ptn_clicked_send_ex_param_slots\0"
    "ptn_start_thickness_slots\0"
    "ptn_stop_thickness_slots\0ptn_wave_get_slots\0"
    "timer_timeout_slots"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ultra_param[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

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

       0        // eod
};

void ultra_param::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ultra_param *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ptn_clicked_disconnect_slots(); break;
        case 1: _t->ptn_clicked_connect_slots(); break;
        case 2: _t->ready_read_slots(); break;
        case 3: _t->ptn_clicked_send_param_slots(); break;
        case 4: _t->ptn_clicked_read_param_slots(); break;
        case 5: _t->ptn_clicked_send_ex_param_slots(); break;
        case 6: _t->ptn_start_thickness_slots(); break;
        case 7: _t->ptn_stop_thickness_slots(); break;
        case 8: _t->ptn_wave_get_slots(); break;
        case 9: _t->timer_timeout_slots(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ultra_param::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ultra_param.data,
    qt_meta_data_ultra_param,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ultra_param::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ultra_param::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ultra_param.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ultra_param::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
