/****************************************************************************
** Meta object code from reading C++ file 'QColorConverterWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QColorConverterWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QColorConverterWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QColorConverterWidget_t {
    QByteArrayData data[18];
    char stringdata0[358];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QColorConverterWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QColorConverterWidget_t qt_meta_stringdata_QColorConverterWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "QColorConverterWidget"
QT_MOC_LITERAL(1, 22, 23), // "onInputPickColorChanged"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 21), // "onCmpPickColorChanged"
QT_MOC_LITERAL(4, 69, 14), // "onCloneClicked"
QT_MOC_LITERAL(5, 84, 28), // "onInputColorComponentChanged"
QT_MOC_LITERAL(6, 113, 26), // "onCmpColorComponentChanged"
QT_MOC_LITERAL(7, 140, 27), // "onRendColorComponentChanged"
QT_MOC_LITERAL(8, 168, 3), // "val"
QT_MOC_LITERAL(9, 172, 19), // "onColorSpaceChanged"
QT_MOC_LITERAL(10, 192, 5), // "index"
QT_MOC_LITERAL(11, 198, 24), // "onInputColorSpaceChanged"
QT_MOC_LITERAL(12, 223, 23), // "onRendColorSpaceChanged"
QT_MOC_LITERAL(13, 247, 25), // "onOutputColorSpaceChanged"
QT_MOC_LITERAL(14, 273, 23), // "onOutputExposureChanged"
QT_MOC_LITERAL(15, 297, 20), // "onOutputGammaChanged"
QT_MOC_LITERAL(16, 318, 19), // "onRenderModeChanged"
QT_MOC_LITERAL(17, 338, 19) // "onOutputModeChanged"

    },
    "QColorConverterWidget\0onInputPickColorChanged\0"
    "\0onCmpPickColorChanged\0onCloneClicked\0"
    "onInputColorComponentChanged\0"
    "onCmpColorComponentChanged\0"
    "onRendColorComponentChanged\0val\0"
    "onColorSpaceChanged\0index\0"
    "onInputColorSpaceChanged\0"
    "onRendColorSpaceChanged\0"
    "onOutputColorSpaceChanged\0"
    "onOutputExposureChanged\0onOutputGammaChanged\0"
    "onRenderModeChanged\0onOutputModeChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QColorConverterWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x0a /* Public */,
       3,    1,   87,    2, 0x0a /* Public */,
       4,    0,   90,    2, 0x0a /* Public */,
       5,    1,   91,    2, 0x0a /* Public */,
       6,    1,   94,    2, 0x0a /* Public */,
       7,    1,   97,    2, 0x0a /* Public */,
       9,    1,  100,    2, 0x0a /* Public */,
      11,    1,  103,    2, 0x0a /* Public */,
      12,    1,  106,    2, 0x0a /* Public */,
      13,    1,  109,    2, 0x0a /* Public */,
      14,    1,  112,    2, 0x0a /* Public */,
      15,    1,  115,    2, 0x0a /* Public */,
      16,    1,  118,    2, 0x0a /* Public */,
      17,    1,  121,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void QColorConverterWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QColorConverterWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onInputPickColorChanged((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 1: _t->onCmpPickColorChanged((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 2: _t->onCloneClicked(); break;
        case 3: _t->onInputColorComponentChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->onCmpColorComponentChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->onRendColorComponentChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->onColorSpaceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onInputColorSpaceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onRendColorSpaceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->onOutputColorSpaceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->onOutputExposureChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->onOutputGammaChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->onRenderModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->onOutputModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QColorConverterWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_QColorConverterWidget.data,
    qt_meta_data_QColorConverterWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QColorConverterWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QColorConverterWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QColorConverterWidget.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int QColorConverterWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
