// Copyright (C) 2016 The Qt Company Ltd and/or its subsidiary(-ies).
// Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QT3DQUICKVALUETYPES_P_H
#define QT3DQUICKVALUETYPES_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/QColor>
#include <QtGui/QMatrix4x4>
#include <QtGui/QQuaternion>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>

#include <Qt3DQuick/private/qt3dquick_global_p.h>
#include <QtQml/private/qqmlvaluetype_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DCore {
namespace Quick {

class Q_3DQUICKSHARED_PRIVATE_EXPORT QQuick3DColorValueType
{
    QColor v;
    Q_PROPERTY(qreal r READ r WRITE setR FINAL)
    Q_PROPERTY(qreal g READ g WRITE setG FINAL)
    Q_PROPERTY(qreal b READ b WRITE setB FINAL)
    Q_PROPERTY(qreal a READ a WRITE setA FINAL)
    Q_PROPERTY(qreal hsvHue READ hsvHue WRITE setHsvHue FINAL)
    Q_PROPERTY(qreal hsvSaturation READ hsvSaturation WRITE setHsvSaturation FINAL)
    Q_PROPERTY(qreal hsvValue READ hsvValue WRITE setHsvValue FINAL)
    Q_PROPERTY(qreal hslHue READ hslHue WRITE setHslHue FINAL)
    Q_PROPERTY(qreal hslSaturation READ hslSaturation WRITE setHslSaturation FINAL)
    Q_PROPERTY(qreal hslLightness READ hslLightness WRITE setHslLightness FINAL)
    Q_PROPERTY(bool valid READ isValid)
    Q_GADGET
    QML_ADDED_IN_VERSION(2, 0)
    QML_FOREIGN(QColor)
    QML_VALUE_TYPE(color)
    QML_EXTENDED(QQuick3DColorValueType)

public:
    static QVariant create(const QJSValue &params);

    Q_INVOKABLE QString toString() const;

    Q_INVOKABLE QVariant alpha(qreal value) const;
    Q_INVOKABLE QVariant lighter(qreal factor = 1.5) const;
    Q_INVOKABLE QVariant darker(qreal factor = 2.0) const;
    Q_INVOKABLE QVariant tint(QVariant factor) const;

    qreal r() const;
    qreal g() const;
    qreal b() const;
    qreal a() const;
    qreal hsvHue() const;
    qreal hsvSaturation() const;
    qreal hsvValue() const;
    qreal hslHue() const;
    qreal hslSaturation() const;
    qreal hslLightness() const;
    bool isValid() const;
    void setR(qreal);
    void setG(qreal);
    void setB(qreal);
    void setA(qreal);
    void setHsvHue(qreal);
    void setHsvSaturation(qreal);
    void setHsvValue(qreal);
    void setHslHue(qreal);
    void setHslSaturation(qreal);
    void setHslLightness(qreal);
};

class Q_3DQUICKSHARED_PRIVATE_EXPORT QQuick3DMatrix4x4ValueType
{
    QMatrix4x4 v;
    Q_PROPERTY(qreal m11 READ m11 WRITE setM11 FINAL)
    Q_PROPERTY(qreal m12 READ m12 WRITE setM12 FINAL)
    Q_PROPERTY(qreal m13 READ m13 WRITE setM13 FINAL)
    Q_PROPERTY(qreal m14 READ m14 WRITE setM14 FINAL)
    Q_PROPERTY(qreal m21 READ m21 WRITE setM21 FINAL)
    Q_PROPERTY(qreal m22 READ m22 WRITE setM22 FINAL)
    Q_PROPERTY(qreal m23 READ m23 WRITE setM23 FINAL)
    Q_PROPERTY(qreal m24 READ m24 WRITE setM24 FINAL)
    Q_PROPERTY(qreal m31 READ m31 WRITE setM31 FINAL)
    Q_PROPERTY(qreal m32 READ m32 WRITE setM32 FINAL)
    Q_PROPERTY(qreal m33 READ m33 WRITE setM33 FINAL)
    Q_PROPERTY(qreal m34 READ m34 WRITE setM34 FINAL)
    Q_PROPERTY(qreal m41 READ m41 WRITE setM41 FINAL)
    Q_PROPERTY(qreal m42 READ m42 WRITE setM42 FINAL)
    Q_PROPERTY(qreal m43 READ m43 WRITE setM43 FINAL)
    Q_PROPERTY(qreal m44 READ m44 WRITE setM44 FINAL)
    Q_GADGET
    QML_ADDED_IN_VERSION(2, 0)
    QML_FOREIGN(QMatrix4x4)
    QML_VALUE_TYPE(matrix4x4)
    QML_EXTENDED(QQuick3DMatrix4x4ValueType)

public:
    static QVariant create(const QJSValue &params);

    qreal m11() const { return v(0, 0); }
    qreal m12() const { return v(0, 1); }
    qreal m13() const { return v(0, 2); }
    qreal m14() const { return v(0, 3); }
    qreal m21() const { return v(1, 0); }
    qreal m22() const { return v(1, 1); }
    qreal m23() const { return v(1, 2); }
    qreal m24() const { return v(1, 3); }
    qreal m31() const { return v(2, 0); }
    qreal m32() const { return v(2, 1); }
    qreal m33() const { return v(2, 2); }
    qreal m34() const { return v(2, 3); }
    qreal m41() const { return v(3, 0); }
    qreal m42() const { return v(3, 1); }
    qreal m43() const { return v(3, 2); }
    qreal m44() const { return v(3, 3); }

    void setM11(qreal value) { v(0, 0) = value; }
    void setM12(qreal value) { v(0, 1) = value; }
    void setM13(qreal value) { v(0, 2) = value; }
    void setM14(qreal value) { v(0, 3) = value; }
    void setM21(qreal value) { v(1, 0) = value; }
    void setM22(qreal value) { v(1, 1) = value; }
    void setM23(qreal value) { v(1, 2) = value; }
    void setM24(qreal value) { v(1, 3) = value; }
    void setM31(qreal value) { v(2, 0) = value; }
    void setM32(qreal value) { v(2, 1) = value; }
    void setM33(qreal value) { v(2, 2) = value; }
    void setM34(qreal value) { v(2, 3) = value; }
    void setM41(qreal value) { v(3, 0) = value; }
    void setM42(qreal value) { v(3, 1) = value; }
    void setM43(qreal value) { v(3, 2) = value; }
    void setM44(qreal value) { v(3, 3) = value; }

    Q_INVOKABLE void translate(const QVector3D &t) { v.translate(t); }
    Q_INVOKABLE void rotate(float angle, const QVector3D &axis) { v.rotate(angle, axis); }
    Q_INVOKABLE void scale(float s) { v.scale(s); }
    Q_INVOKABLE void scale(float sx, float sy, float sz) { v.scale(sx, sy, sz); }
    Q_INVOKABLE void scale(const QVector3D &s) { v.scale(s); }
    Q_INVOKABLE void lookAt(const QVector3D &eye, const QVector3D &center, const QVector3D &up) { v.lookAt(eye, center, up); }

    Q_INVOKABLE QMatrix4x4 times(const QMatrix4x4 &m) const;
    Q_INVOKABLE QVector4D times(const QVector4D &vec) const;
    Q_INVOKABLE QVector3D times(const QVector3D &vec) const;
    Q_INVOKABLE QMatrix4x4 times(qreal factor) const;
    Q_INVOKABLE QMatrix4x4 plus(const QMatrix4x4 &m) const;
    Q_INVOKABLE QMatrix4x4 minus(const QMatrix4x4 &m) const;

    Q_INVOKABLE QVector4D row(int n) const;
    Q_INVOKABLE QVector4D column(int m) const;

    Q_INVOKABLE qreal determinant() const;
    Q_INVOKABLE QMatrix4x4 inverted() const;
    Q_INVOKABLE QMatrix4x4 transposed() const;

    Q_INVOKABLE bool fuzzyEquals(const QMatrix4x4 &m, qreal epsilon) const;
    Q_INVOKABLE bool fuzzyEquals(const QMatrix4x4 &m) const;
};

class Q_3DQUICKSHARED_PRIVATE_EXPORT QQuick3DVector2DValueType
{
    QVector2D v;
    Q_PROPERTY(qreal x READ x WRITE setX FINAL)
    Q_PROPERTY(qreal y READ y WRITE setY FINAL)
    Q_GADGET
    QML_ADDED_IN_VERSION(2, 0)
    QML_FOREIGN(QVector2D)
    QML_VALUE_TYPE(vector2d)
    QML_EXTENDED(QQuick3DVector2DValueType)

public:
    static QVariant create(const QJSValue &params);

    Q_INVOKABLE QString toString() const;

    qreal x() const;
    qreal y() const;
    void setX(qreal);
    void setY(qreal);

    Q_INVOKABLE qreal dotProduct(const QVector2D &vec) const;
    Q_INVOKABLE QVector2D times(const QVector2D &vec) const;
    Q_INVOKABLE QVector2D times(qreal scalar) const;
    Q_INVOKABLE QVector2D plus(const QVector2D &vec) const;
    Q_INVOKABLE QVector2D minus(const QVector2D &vec) const;
    Q_INVOKABLE QVector2D normalized() const;
    Q_INVOKABLE qreal length() const;
    Q_INVOKABLE QVector3D toVector3d() const;
    Q_INVOKABLE QVector4D toVector4d() const;
    Q_INVOKABLE bool fuzzyEquals(const QVector2D &vec, qreal epsilon) const;
    Q_INVOKABLE bool fuzzyEquals(const QVector2D &vec) const;
};

class Q_3DQUICKSHARED_PRIVATE_EXPORT QQuick3DVector3DValueType
{
    QVector3D v;
    Q_PROPERTY(qreal x READ x WRITE setX FINAL)
    Q_PROPERTY(qreal y READ y WRITE setY FINAL)
    Q_PROPERTY(qreal z READ z WRITE setZ FINAL)
    Q_GADGET
    QML_ADDED_IN_VERSION(2, 0)
    QML_FOREIGN(QVector3D)
    QML_VALUE_TYPE(vector3d)
    QML_EXTENDED(QQuick3DVector3DValueType)

public:
    static QVariant create(const QJSValue &params);

    Q_INVOKABLE QString toString() const;

    qreal x() const;
    qreal y() const;
    qreal z() const;
    void setX(qreal);
    void setY(qreal);
    void setZ(qreal);

    Q_INVOKABLE QVector3D crossProduct(const QVector3D &vec) const;
    Q_INVOKABLE qreal dotProduct(const QVector3D &vec) const;
    Q_INVOKABLE QVector3D times(const QMatrix4x4 &m) const;
    Q_INVOKABLE QVector3D times(const QVector3D &vec) const;
    Q_INVOKABLE QVector3D times(qreal scalar) const;
    Q_INVOKABLE QVector3D plus(const QVector3D &vec) const;
    Q_INVOKABLE QVector3D minus(const QVector3D &vec) const;
    Q_INVOKABLE QVector3D normalized() const;
    Q_INVOKABLE qreal length() const;
    Q_INVOKABLE QVector2D toVector2d() const;
    Q_INVOKABLE QVector4D toVector4d() const;
    Q_INVOKABLE bool fuzzyEquals(const QVector3D &vec, qreal epsilon) const;
    Q_INVOKABLE bool fuzzyEquals(const QVector3D &vec) const;
};

class Q_3DQUICKSHARED_PRIVATE_EXPORT QQuick3DVector4DValueType
{
    QVector4D v;
    Q_PROPERTY(qreal x READ x WRITE setX FINAL)
    Q_PROPERTY(qreal y READ y WRITE setY FINAL)
    Q_PROPERTY(qreal z READ z WRITE setZ FINAL)
    Q_PROPERTY(qreal w READ w WRITE setW FINAL)
    Q_GADGET
    QML_ADDED_IN_VERSION(2, 0)
    QML_FOREIGN(QVector4D)
    QML_VALUE_TYPE(vector4d)
    QML_EXTENDED(QQuick3DVector4DValueType)

public:
    static QVariant create(const QJSValue &params);

    Q_INVOKABLE QString toString() const;

    qreal x() const;
    qreal y() const;
    qreal z() const;
    qreal w() const;
    void setX(qreal);
    void setY(qreal);
    void setZ(qreal);
    void setW(qreal);

    Q_INVOKABLE qreal dotProduct(const QVector4D &vec) const;
    Q_INVOKABLE QVector4D times(const QVector4D &vec) const;
    Q_INVOKABLE QVector4D times(const QMatrix4x4 &m) const;
    Q_INVOKABLE QVector4D times(qreal scalar) const;
    Q_INVOKABLE QVector4D plus(const QVector4D &vec) const;
    Q_INVOKABLE QVector4D minus(const QVector4D &vec) const;
    Q_INVOKABLE QVector4D normalized() const;
    Q_INVOKABLE qreal length() const;
    Q_INVOKABLE QVector2D toVector2d() const;
    Q_INVOKABLE QVector3D toVector3d() const;
    Q_INVOKABLE bool fuzzyEquals(const QVector4D &vec, qreal epsilon) const;
    Q_INVOKABLE bool fuzzyEquals(const QVector4D &vec) const;
};

class Q_3DQUICKSHARED_PRIVATE_EXPORT QQuick3DQuaternionValueType
{
    QQuaternion v;
    Q_PROPERTY(qreal scalar READ scalar WRITE setScalar)
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(qreal z READ z WRITE setZ)
    Q_GADGET
    QML_ADDED_IN_VERSION(2, 0)
    QML_FOREIGN(QQuaternion)
    QML_VALUE_TYPE(quaternion)
    QML_EXTENDED(QQuick3DQuaternionValueType)

public:
    static QVariant create(const QJSValue &params);

    Q_INVOKABLE QString toString() const;

    qreal scalar() const;
    qreal x() const;
    qreal y() const;
    qreal z() const;
    void setScalar(qreal);
    void setX(qreal);
    void setY(qreal);
    void setZ(qreal);
};

} // namespace Quick
} // namespace Qt3DCore

QT_END_NAMESPACE

#endif // QT3DQUICKVALUETYPES_P_H
