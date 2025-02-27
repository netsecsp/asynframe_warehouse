// Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QT3DRENDER_RENDER_NODEFUNCTOR_P_H
#define QT3DRENDER_RENDER_NODEFUNCTOR_P_H

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

#include <Qt3DCore/qnode.h>
#include <Qt3DRender/private/backendnode_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

namespace Render {

class AbstractRenderer;

template<class Backend, class Manager>
class NodeFunctor : public Qt3DCore::QBackendNodeMapper
{
public:
    explicit NodeFunctor(AbstractRenderer *renderer)
        : m_manager(renderer->nodeManagers()->manager<Backend, Manager>())
        , m_renderer(renderer)
    {
    }

    Qt3DCore::QBackendNode *create(Qt3DCore::QNodeId id) const final
    {
        Backend *backend = m_manager->getOrCreateResource(id);
        backend->setRenderer(m_renderer);
        return backend;
    }

    Qt3DCore::QBackendNode *get(Qt3DCore::QNodeId id) const final
    {
        return m_manager->lookupResource(id);
    }

    void destroy(Qt3DCore::QNodeId id) const final
    {
        m_manager->releaseResource(id);
    }

private:
    Manager *m_manager;
    AbstractRenderer *m_renderer;
};

} // namespace Render

} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_NODEFUNCTOR_P_H
