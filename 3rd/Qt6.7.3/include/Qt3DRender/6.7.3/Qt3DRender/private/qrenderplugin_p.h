// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QT3DRENDER_RENDER_QRENDERPLUGIN_P_H
#define QT3DRENDER_RENDER_QRENDERPLUGIN_P_H

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

#include <private/qt3drender_global_p.h>

#include <Qt3DCore/qbackendnode.h>
#include <Qt3DRender/qrenderaspect.h>

#include <QtCore/qobject.h>
#include <QtCore/qstringlist.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

namespace Render {

class AbstractRenderer;

class Q_3DRENDERSHARED_PRIVATE_EXPORT QRenderPlugin
{
public:
    virtual bool registerBackendTypes(QRenderAspect *aspect, AbstractRenderer *renderer) = 0;
    virtual bool unregisterBackendTypes(QRenderAspect *aspect) = 0;

protected:
    void registerBackendType(QRenderAspect *aspect, const QMetaObject &obj, const Qt3DCore::QBackendNodeMapperPtr &functor)
    {
        aspect->registerBackendType(obj, functor);
    }
    void unregisterBackendType(QRenderAspect *aspect, const QMetaObject &obj)
    {
        aspect->unregisterBackendType(obj);
    }
};

} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_QRENDERPLUGIN_P_H
