/****************************************************************************
** Meta object code from reading C++ file 'compProgramGenerate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../compProgramGenerate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'compProgramGenerate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_compProgramGenerate_t {
    QByteArrayData data[6];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_compProgramGenerate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_compProgramGenerate_t qt_meta_stringdata_compProgramGenerate = {
    {
QT_MOC_LITERAL(0, 0, 19), // "compProgramGenerate"
QT_MOC_LITERAL(1, 20, 28), // "accept_tool_length_threshold"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 9), // "threshold"
QT_MOC_LITERAL(4, 60, 8), // "standard"
QT_MOC_LITERAL(5, 69, 13) // "smooth_factor"

    },
    "compProgramGenerate\0accept_tool_length_threshold\0"
    "\0threshold\0standard\0smooth_factor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_compProgramGenerate[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Float, QMetaType::Float,    3,    4,    5,

       0        // eod
};

void compProgramGenerate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<compProgramGenerate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->accept_tool_length_threshold((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject compProgramGenerate::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_compProgramGenerate.data,
    qt_meta_data_compProgramGenerate,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *compProgramGenerate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *compProgramGenerate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_compProgramGenerate.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int compProgramGenerate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
