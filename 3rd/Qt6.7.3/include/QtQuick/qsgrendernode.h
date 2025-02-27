// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QSGRENDERNODE_H
#define QSGRENDERNODE_H

#include <QtQuick/qsgnode.h>

QT_BEGIN_NAMESPACE

class QSGRenderNodePrivate;
class QRhiRenderTarget;
class QRhiCommandBuffer;

class Q_QUICK_EXPORT QSGRenderNode : public QSGNode
{
public:
    enum StateFlag {
        DepthState = 0x01,
        StencilState = 0x02,
        ScissorState = 0x04,
        ColorState = 0x08,
        BlendState = 0x10,
        CullState = 0x20,
        ViewportState = 0x40,
        RenderTargetState = 0x80
    };
    Q_DECLARE_FLAGS(StateFlags, StateFlag)

    enum RenderingFlag {
        BoundedRectRendering = 0x01,
        DepthAwareRendering = 0x02,
        OpaqueRendering = 0x04,
        NoExternalRendering = 0x08
    };
    Q_DECLARE_FLAGS(RenderingFlags, RenderingFlag)

    struct Q_QUICK_EXPORT RenderState {
        virtual ~RenderState();
        virtual const QMatrix4x4 *projectionMatrix() const = 0;
        virtual QRect scissorRect() const = 0;
        virtual bool scissorEnabled() const = 0;
        virtual int stencilValue() const = 0;
        virtual bool stencilEnabled() const = 0;
        virtual const QRegion *clipRegion() const = 0;
        virtual void *get(const char *state) const;
    };

    QSGRenderNode();
    ~QSGRenderNode() override;

    virtual StateFlags changedStates() const;
    virtual void prepare();
    virtual void render(const RenderState *state) = 0;
    virtual void releaseResources();
    virtual RenderingFlags flags() const;
    virtual QRectF rect() const;

    const QMatrix4x4 *projectionMatrix() const;
    const QMatrix4x4 *matrix() const;
    const QSGClipNode *clipList() const;
    qreal inheritedOpacity() const;
    QRhiRenderTarget *renderTarget() const;
    QRhiCommandBuffer *commandBuffer() const;

private:
    QSGRenderNodePrivate *d;
    friend class QSGRenderNodePrivate;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QSGRenderNode::StateFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(QSGRenderNode::RenderingFlags)

QT_END_NAMESPACE

#endif
