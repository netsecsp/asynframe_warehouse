// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of Qt Designer.  This header
// file may change from version to version without notice, or even be removed.
//
// We mean it.
//

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "shared_global_p.h"
#include "shared_enums_p.h"

#include <QtCore/qshareddata.h>
#include <QtCore/qmap.h>
#include <QtCore/qpair.h>
#include <QtCore/qobject.h>
#include <QtCore/qstringlist.h>

QT_BEGIN_NAMESPACE

class QDesignerFormEditorInterface;
class QDesignerCustomWidgetInterface;
class QDesignerPluginManagerPrivate;

class QDesignerCustomWidgetSharedData;

/* Information contained in the Dom XML of a custom widget. */
class QDESIGNER_SHARED_EXPORT QDesignerCustomWidgetData {
public:
    // StringPropertyType: validation mode and translatable flag.
    using StringPropertyType = std::pair<qdesigner_internal::TextPropertyValidationMode, bool>;

    explicit QDesignerCustomWidgetData(const QString &pluginPath = QString());

    enum ParseResult { ParseOk, ParseWarning, ParseError };
    ParseResult parseXml(const QString &xml, const QString &name, QString *errorMessage);

    QDesignerCustomWidgetData(const QDesignerCustomWidgetData&);
    QDesignerCustomWidgetData& operator=(const QDesignerCustomWidgetData&);
    ~QDesignerCustomWidgetData();

    bool isNull() const;

    QString pluginPath() const;

    // Data as parsed from the widget's domXML().
    QString xmlClassName() const;
    // Optional. The language the plugin is supposed to be used with.
    QString xmlLanguage() const;
    // Optional. method used to add pages to a container with a container extension
    QString xmlAddPageMethod() const;
    // Optional. Base class
    QString xmlExtends() const;
    // Optional. The name to be used in the widget box.
    QString xmlDisplayName() const;
    // Type of a string property
    bool xmlStringPropertyType(const QString &name, StringPropertyType *type) const;
    // Custom tool tip of property
    QString propertyToolTip(const QString &name) const;

private:
    QSharedDataPointer<QDesignerCustomWidgetSharedData> m_d;
};

class QDESIGNER_SHARED_EXPORT QDesignerPluginManager: public QObject
{
    Q_OBJECT
public:
    using CustomWidgetList = QList<QDesignerCustomWidgetInterface *>;

    explicit QDesignerPluginManager(QDesignerFormEditorInterface *core);
    explicit QDesignerPluginManager(const QStringList &pluginPaths,
                                    QDesignerFormEditorInterface *core);
    ~QDesignerPluginManager() override;

    QDesignerFormEditorInterface *core() const;

    QObject *instance(const QString &plugin) const;

    QStringList registeredPlugins() const;

    QStringList findPlugins(const QString &path);

    QStringList pluginPaths() const;
    void setPluginPaths(const QStringList &plugin_paths);

    QStringList disabledPlugins() const;
    void setDisabledPlugins(const QStringList &disabled_plugins);

    QStringList failedPlugins() const;
    QString failureReason(const QString &pluginName) const;

    QObjectList instances() const;

    CustomWidgetList registeredCustomWidgets() const;
    QDesignerCustomWidgetData customWidgetData(QDesignerCustomWidgetInterface *w) const;
    QDesignerCustomWidgetData customWidgetData(const QString &className) const;

    bool registerNewPlugins();

    static QStringList defaultPluginPaths();

public slots:
    bool syncSettings();
    void ensureInitialized();

private:
    void updateRegisteredPlugins();
    void registerPath(const QString &path);
    void registerPlugin(const QString &plugin);

private:
    QDesignerPluginManagerPrivate *m_d;
};

QT_END_NAMESPACE

#endif // PLUGINMANAGER_H
