// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QQUICKFUSIONDIAL_P_H
#define QQUICKFUSIONDIAL_P_H

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

#include <QtQuick/qquickpainteditem.h>
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE

class QQuickFusionDial : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(bool highlight READ highlight WRITE setHighlight FINAL)
    QML_NAMED_ELEMENT(DialImpl)
    QML_ADDED_IN_VERSION(2, 3)

public:
    explicit QQuickFusionDial(QQuickItem *parent = nullptr);

    bool highlight() const;
    void setHighlight(bool highlight);

    void paint(QPainter *painter) override;

private:
    bool m_highlight = false;
};

QT_END_NAMESPACE

#endif // QQUICKFUSIONDIAL_P_H
