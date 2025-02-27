// Copyright (C) 2016 Research In Motion
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only
#ifndef QAMBIENTTEMPERATURESENSOR_P_H
#define QAMBIENTTEMPERATURESENSOR_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists purely as an
// implementation detail. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE

class QAmbientTemperatureReadingPrivate
{
public:
    QAmbientTemperatureReadingPrivate()
        : temperature(0)
    {
    }

    qreal temperature;
};

QT_END_NAMESPACE

#endif
