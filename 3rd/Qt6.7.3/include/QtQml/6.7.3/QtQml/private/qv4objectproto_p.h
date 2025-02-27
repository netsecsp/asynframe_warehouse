// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only
#ifndef QV4ECMAOBJECTS_P_H
#define QV4ECMAOBJECTS_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qv4object_p.h"
#include "qv4functionobject_p.h"
#include <QtCore/qnumeric.h>

QT_BEGIN_NAMESPACE

namespace QV4 {

namespace Heap {

struct ObjectCtor : FunctionObject {
    void init(QV4::ExecutionContext *scope);
};

}

struct ObjectCtor: FunctionObject
{
    V4_OBJECT2(ObjectCtor, FunctionObject)

    static ReturnedValue virtualCallAsConstructor(const FunctionObject *f, const Value *argv, int argc, const Value *);
    static ReturnedValue virtualCall(const FunctionObject *m, const Value *thisObject, const Value *argv, int argc);
};

struct Q_QML_PRIVATE_EXPORT ObjectPrototype: Object
{
    void init(ExecutionEngine *engine, Object *ctor);

    static ReturnedValue method_assign(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_create(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_defineProperties(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_defineProperty(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_entries(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_freeze(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_getOwnPropertyDescriptor(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_getOwnPropertyDescriptors(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_getOwnPropertyNames(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_getOwnPropertySymbols(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_getPrototypeOf(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_is(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_isExtensible(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_isFrozen(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_isSealed(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_keys(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_preventExtensions(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_seal(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_setPrototypeOf(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_values(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);

    static ReturnedValue method_toString(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_toLocaleString(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_valueOf(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_hasOwnProperty(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_isPrototypeOf(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_propertyIsEnumerable(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);

    static ReturnedValue method_defineGetter(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_defineSetter(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);

    static ReturnedValue method_get_proto(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    static ReturnedValue method_set_proto(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);

    static void toPropertyDescriptor(ExecutionEngine *engine, const Value &v, Property *desc, PropertyAttributes *attrs);
    static ReturnedValue fromPropertyDescriptor(ExecutionEngine *engine, const Property *desc, PropertyAttributes attrs);

    static Heap::ArrayObject *getOwnPropertyNames(ExecutionEngine *v4, const Value &o);
};


}

QT_END_NAMESPACE

#endif // QV4ECMAOBJECTS_P_H
