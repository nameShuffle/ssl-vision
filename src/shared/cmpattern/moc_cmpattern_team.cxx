/****************************************************************************
** Meta object code from reading C++ file 'cmpattern_team.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cmpattern_team.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cmpattern_team.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CMPattern__Team[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      46,   41,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      76,   16,   16,   16, 0x09,
      98,   41,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CMPattern__Team[] = {
    "CMPattern::Team\0\0signalTeamNameChanged()\0"
    "item\0signalChangeOccured(VarType*)\0"
    "slotTeamNameChanged()\0slotChangeOccured(VarType*)\0"
};

void CMPattern::Team::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Team *_t = static_cast<Team *>(_o);
        switch (_id) {
        case 0: _t->signalTeamNameChanged(); break;
        case 1: _t->signalChangeOccured((*reinterpret_cast< VarType*(*)>(_a[1]))); break;
        case 2: _t->slotTeamNameChanged(); break;
        case 3: _t->slotChangeOccured((*reinterpret_cast< VarType*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CMPattern::Team::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CMPattern::Team::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CMPattern__Team,
      qt_meta_data_CMPattern__Team, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CMPattern::Team::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CMPattern::Team::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CMPattern::Team::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMPattern__Team))
        return static_cast<void*>(const_cast< Team*>(this));
    return QObject::qt_metacast(_clname);
}

int CMPattern::Team::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CMPattern::Team::signalTeamNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CMPattern::Team::signalChangeOccured(VarType * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_CMPattern__RobotPattern[] = {

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
      30,   25,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   25,   24,   24, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CMPattern__RobotPattern[] = {
    "CMPattern::RobotPattern\0\0item\0"
    "signalChangeOccured(VarType*)\0"
    "slotChangeOccured(VarType*)\0"
};

void CMPattern::RobotPattern::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RobotPattern *_t = static_cast<RobotPattern *>(_o);
        switch (_id) {
        case 0: _t->signalChangeOccured((*reinterpret_cast< VarType*(*)>(_a[1]))); break;
        case 1: _t->slotChangeOccured((*reinterpret_cast< VarType*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CMPattern::RobotPattern::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CMPattern::RobotPattern::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CMPattern__RobotPattern,
      qt_meta_data_CMPattern__RobotPattern, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CMPattern::RobotPattern::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CMPattern::RobotPattern::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CMPattern::RobotPattern::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMPattern__RobotPattern))
        return static_cast<void*>(const_cast< RobotPattern*>(this));
    return QObject::qt_metacast(_clname);
}

int CMPattern::RobotPattern::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CMPattern::RobotPattern::signalChangeOccured(VarType * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
