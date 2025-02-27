// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QSGCURVEFILLNODE_P_P_H
#define QSGCURVEFILLNODE_P_P_H

#include <QtQuick/private/qtquickexports_p.h>
#include <QtQuick/qsgmaterial.h>

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of a number of Qt sources files.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

QT_BEGIN_NAMESPACE

class QSGCurveFillNode;
class Q_QUICK_PRIVATE_EXPORT QSGCurveFillMaterial : public QSGMaterial
{
public:
    QSGCurveFillMaterial(QSGCurveFillNode *node);
    int compare(const QSGMaterial *other) const override;

    QSGCurveFillNode *node() const
    {
        return m_node;
    }

private:
    QSGMaterialType *type() const override;
    QSGMaterialShader *createShader(QSGRendererInterface::RenderMode renderMode) const override;

    QSGCurveFillNode *m_node;
};

QT_END_NAMESPACE

#endif // QSGCURVEFILLNODE_P_P_H
