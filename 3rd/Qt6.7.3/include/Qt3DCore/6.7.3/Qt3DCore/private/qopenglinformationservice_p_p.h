// Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QT3DCORE_QOPENGLINFORMATIONSERVICE_P_P_H
#define QT3DCORE_QOPENGLINFORMATIONSERVICE_P_P_H

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

#include <Qt3DCore/qt3dcore_global.h>

#include <Qt3DCore/private/qabstractserviceprovider_p.h>
#include <Qt3DCore/private/qservicelocator_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DCore {

class QOpenGLInformationServicePrivate : public QAbstractServiceProviderPrivate
{
public:
    QOpenGLInformationServicePrivate(const QString &description)
        : QAbstractServiceProviderPrivate(QServiceLocator::OpenGLInformation, description)
    {}
};

}

QT_END_NAMESPACE

#endif // QT3DCORE_QOPENGLINFORMATIONSERVICE_P_P_H

