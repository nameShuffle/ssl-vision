/****************************************************************************
** Meta object code from reading C++ file 'plugin_colorthreshold.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "plugin_colorthreshold.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plugin_colorthreshold.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PluginColorThresholdWorker[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   27,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PluginColorThresholdWorker[] = {
    "PluginColorThresholdWorker\0\0"
    "startThresholding()\0process()\0"
};

void PluginColorThresholdWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PluginColorThresholdWorker *_t = static_cast<PluginColorThresholdWorker *>(_o);
        switch (_id) {
        case 0: _t->startThresholding(); break;
        case 1: _t->process(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData PluginColorThresholdWorker::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PluginColorThresholdWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PluginColorThresholdWorker,
      qt_meta_data_PluginColorThresholdWorker, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PluginColorThresholdWorker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PluginColorThresholdWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PluginColorThresholdWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PluginColorThresholdWorker))
        return static_cast<void*>(const_cast< PluginColorThresholdWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int PluginColorThresholdWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void PluginColorThresholdWorker::startThresholding()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE