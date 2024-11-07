/****************************************************************************
** Meta object code from reading C++ file 'modifyuser.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../PI-Edificio/modifyuser.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modifyuser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSModifyUserENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSModifyUserENDCLASS = QtMocHelpers::stringData(
    "ModifyUser",
    "on_pushButton1_clicked",
    "",
    "on_pushButton1_2_clicked",
    "on_listWidget_itemClicked",
    "QListWidgetItem*",
    "item",
    "loadUserList",
    "checkPermissions",
    "std::string",
    "uint8_t",
    "user_permissions"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSModifyUserENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[11];
    char stringdata1[23];
    char stringdata2[1];
    char stringdata3[25];
    char stringdata4[26];
    char stringdata5[17];
    char stringdata6[5];
    char stringdata7[13];
    char stringdata8[17];
    char stringdata9[12];
    char stringdata10[8];
    char stringdata11[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSModifyUserENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSModifyUserENDCLASS_t qt_meta_stringdata_CLASSModifyUserENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "ModifyUser"
        QT_MOC_LITERAL(11, 22),  // "on_pushButton1_clicked"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 24),  // "on_pushButton1_2_clicked"
        QT_MOC_LITERAL(60, 25),  // "on_listWidget_itemClicked"
        QT_MOC_LITERAL(86, 16),  // "QListWidgetItem*"
        QT_MOC_LITERAL(103, 4),  // "item"
        QT_MOC_LITERAL(108, 12),  // "loadUserList"
        QT_MOC_LITERAL(121, 16),  // "checkPermissions"
        QT_MOC_LITERAL(138, 11),  // "std::string"
        QT_MOC_LITERAL(150, 7),  // "uint8_t"
        QT_MOC_LITERAL(158, 16)   // "user_permissions"
    },
    "ModifyUser",
    "on_pushButton1_clicked",
    "",
    "on_pushButton1_2_clicked",
    "on_listWidget_itemClicked",
    "QListWidgetItem*",
    "item",
    "loadUserList",
    "checkPermissions",
    "std::string",
    "uint8_t",
    "user_permissions"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSModifyUserENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x08,    1 /* Private */,
       3,    0,   45,    2, 0x08,    2 /* Private */,
       4,    1,   46,    2, 0x08,    3 /* Private */,
       7,    0,   49,    2, 0x08,    5 /* Private */,
       8,    1,   50,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    0x80000000 | 9, 0x80000000 | 10,   11,

       0        // eod
};

Q_CONSTINIT const QMetaObject ModifyUser::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSModifyUserENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSModifyUserENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSModifyUserENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ModifyUser, std::true_type>,
        // method 'on_pushButton1_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton1_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_listWidget_itemClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'loadUserList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkPermissions'
        QtPrivate::TypeAndForceComplete<std::string, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>
    >,
    nullptr
} };

void ModifyUser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ModifyUser *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton1_clicked(); break;
        case 1: _t->on_pushButton1_2_clicked(); break;
        case 2: _t->on_listWidget_itemClicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 3: _t->loadUserList(); break;
        case 4: { std::string _r = _t->checkPermissions((*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *ModifyUser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModifyUser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSModifyUserENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ModifyUser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
