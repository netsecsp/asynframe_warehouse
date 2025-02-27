// Copyright (C) 2016 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, author Milian Wolff <milian.wolff@kdab.com>
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QMETAOBJECTPUBLISHER_P_H
#define QMETAOBJECTPUBLISHER_P_H

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

#include "qwebchannelglobal.h"
#include "signalhandler_p.h"

#include <QStringList>
#include <QMetaObject>
#include <QBasicTimer>
#include <QPointer>
#include <QProperty>
#include <QJsonObject>
#include <QQueue>
#include <QSet>

#include <unordered_map>

class tst_bench_QWebChannel;

QT_BEGIN_NAMESPACE

// NOTE: keep in sync with corresponding maps in qwebchannel.js and WebChannelTest.qml
enum MessageType {
    TypeInvalid = 0,

    TYPES_FIRST_VALUE = 1,

    TypeSignal = 1,
    TypePropertyUpdate = 2,
    TypeInit = 3,
    TypeIdle = 4,
    TypeDebug = 5,
    TypeInvokeMethod = 6,
    TypeConnectToSignal = 7,
    TypeDisconnectFromSignal = 8,
    TypeSetProperty = 9,
    TypeResponse = 10,

    TYPES_LAST_VALUE = 10
};

class QMetaObjectPublisher;
class QWebChannel;
class QWebChannelAbstractTransport;

struct QWebChannelPropertyChangeNotifier : QPropertyObserver
{
    QWebChannelPropertyChangeNotifier(QMetaObjectPublisher *publisher, const QObject *object, int propertyIndex)
        : QPropertyObserver(&QWebChannelPropertyChangeNotifier::notify),
          publisher(publisher), object(object), propertyIndex(propertyIndex)
    {
    }

    QMetaObjectPublisher *publisher = nullptr;
    const QObject *object = nullptr;
    int propertyIndex = 0;
    static void notify(QPropertyObserver *, QUntypedPropertyData *);
};

class Q_WEBCHANNEL_EXPORT QMetaObjectPublisher : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int propertyUpdateIntervalTime READ propertyUpdateInterval WRITE
                       setPropertyUpdateInterval)
public:
    explicit QMetaObjectPublisher(QWebChannel *webChannel);
    virtual ~QMetaObjectPublisher();

    /**
     * Register @p object under the given @p id.
     *
     * The properties, signals and public methods of the QObject are
     * published to the remote client, where an object with the given identifier
     * is constructed.
     *
     * TODO: This must be called, before clients are initialized.
     */
    void registerObject(const QString &id, QObject *object);

    /**
     * Send the given message to all known transports.
     */
    void broadcastMessage(const QJsonObject &message) const;

    /**
     * Enqueue the given @p message to all known transports.
     */
    void enqueueBroadcastMessage(const QJsonObject &message);

    /**
     * Enqueue the given @p message to @p transport.
     */
    void enqueueMessage(const QJsonObject &message, QWebChannelAbstractTransport *transport);

    /**
     * If client for given @p transport is idle, send queued messaged to @p transport and then mark
     * the client as not idle.
     */
    void sendEnqueuedPropertyUpdates(QWebChannelAbstractTransport *transport);

    /**
     * Serialize the QMetaObject of @p object and return it in JSON form.
     */
    QJsonObject classInfoForObject(const QObject *object, QWebChannelAbstractTransport *transport);

    /**
     * Set the client to idle or busy for a single @p transport, based on the value of @p isIdle.
     */
    void setClientIsIdle(bool isIdle, QWebChannelAbstractTransport *transport);

    /**
     * Check that client is idle for @p transport.
     */
    bool isClientIdle(QWebChannelAbstractTransport *transport);

    /**
     * Initialize clients by sending them the class information of the registered objects.
     *
     * Furthermore, if that was not done already, connect to their property notify signals.
     */
    QJsonObject initializeClient(QWebChannelAbstractTransport *transport);

    /**
     * Go through all properties of the given object and connect to their notify signal.
     *
     * When receiving a notify signal, it will store the information in pendingPropertyUpdates which
     * gets send via a Qt.propertyUpdate message to the server when the grouping timer timeouts.
     */
    void initializePropertyUpdates(QObject *const object, const QJsonObject &objectInfo);

    /**
     * Send the clients the new property values since the last time this function was invoked.
     *
     * This is a grouped batch of all properties for which their notify signal was emitted.
     * The list of signals as well as the arguments they contained, are also transmitted to
     * the remote clients.
     *
     * @sa timer, initializePropertyUpdates
     */
    void sendPendingPropertyUpdates();

    /**
     * Helper function for the invokeMehtods below
     */
    QVariant invokeMethod_helper(QObject *const object, const QMetaMethod &method,
                                 const QJsonArray &args);

    /**
     * Invoke the @p method on @p object with the arguments @p args.
     *
     * The return value of the method invocation is then serialized and a response message
     * is returned.
     */
    QVariant invokeMethod(QObject *const object, const QMetaMethod &method, const QJsonArray &args);

    /**
     * Invoke the method of index @p methodIndex on @p object with the arguments @p args.
     *
     * The return value of the method invocation is then serialized and a response message
     * is returned.
     */
    QVariant invokeMethod(QObject *const object, const int methodIndex, const QJsonArray &args);

    /**
     * Invoke the method of name @p methodName on @p object with the arguments @p args.
     *
     * This method performs overload resolution on @p methodName.
     *
     * The return value of the method invocation is then serialized and a response message
     * is returned.
     */
    QVariant invokeMethod(QObject *const object, const QByteArray &methodName, const QJsonArray &args);

    /**
     * Set the value of property @p propertyIndex on @p object to @p value.
     */
    void setProperty(QObject *object, const int propertyIndex, const QJsonValue &value);

    /**
     * Callback of the signalHandler which forwards the signal invocation to the webchannel clients.
     */
    void signalEmitted(const QObject *object, const int signalIndex, const QVariantList &arguments);

    /**
     * Callback for bindable property value changes which forwards the change to the webchannel clients.
     */
    void propertyValueChanged(const QObject *object, const int propertyIndex);

    /**
     * Called after a property has been updated. Starts the update timer if
     * the client is idle and updates are not blocked.
     */
    void startPropertyUpdateTimer(bool forceRestart = false);

    /**
     * Callback for registered or wrapped objects which erases all data related to @p object.
     *
     * @sa signalEmitted
     */
    void objectDestroyed(const QObject *object);

    QObject *unwrapObject(const QString &objectId) const;
    QVariant unwrapMap(QVariantMap map) const;
    QVariant unwrapList(QVariantList list) const;
    QVariant unwrapVariant(const QVariant &value) const;

    QVariant toVariant(const QJsonValue &value, int targetType) const;

    /**
     * Assigns a score for the conversion from @p value to @p targetType.
     *
     * Scores can be compared to find the best match. The lower the score, the
     * more preferable is the conversion.
     *
     * @sa invokeMethod, methodOverloadBadness
     */
    int conversionScore(const QJsonValue &value, int targetType) const;

    /**
     * Scores @p method against @p args.
     *
     * Scores can be compared to find the best match from a set of overloads.
     * The lower the score, the more preferable is the method.
     *
     * @sa invokeMethod, conversionScore
     */
    int methodOverloadBadness(const QMetaMethod &method, const QJsonArray &args) const;

    /**
     * Remove wrapped objects which last transport relation is with the passed transport object.
     */
    void transportRemoved(QWebChannelAbstractTransport *transport);

    /**
     * Given a QVariant containing a QObject*, wrap the object and register for property updates
     * return the objects class information.
     *
     * All other input types are returned as-is.
     */
    QJsonValue wrapResult(const QVariant &result, QWebChannelAbstractTransport *transport,
                          const QString &parentObjectId = QString());

    /**
     * Convert a list of variant values for consumption by the client.
     *
     * This properly handles QML values and also wraps the result if required.
     */
    QJsonArray wrapList(const QVariantList &list, QWebChannelAbstractTransport *transport,
                          const QString &parentObjectId = QString());

    /**
     * Convert a variant map for consumption by the client.
     *
     * This properly handles QML values and also wraps the result if required.
     */
    QJsonObject wrapMap(const QVariantMap &map, QWebChannelAbstractTransport *transport,
                          const QString &parentObjectId = QString());

    /**
     * Invoke delete later on @p object.
     */
    void deleteWrappedObject(QObject *object) const;

    /**
     * The property update interval in milliseconds.
     *
     * This interval can be changed to a different interval in milliseconds by
     * setting it to a positive value. Property updates are batched and sent out
     * after the interval expires. If set to zero, the updates occurring within a
     * single event loop run are batched and sent out on the next run.
     * If negative, updates will be sent immediately.
     * Default value is 50 milliseconds.
     */
    int propertyUpdateInterval();
    void setPropertyUpdateInterval(int ms);

    /**
     * When updates are blocked, no property updates are transmitted to remote clients.
     */
    void setBlockUpdates(bool block);
    bool blockUpdates() const;

Q_SIGNALS:
    void blockUpdatesChanged(bool block);

public Q_SLOTS:
    /**
     * Handle the @p message and if needed send a response to @p transport.
     */
    void handleMessage(const QJsonObject &message, QWebChannelAbstractTransport *transport);

protected:
    void timerEvent(QTimerEvent *) override;

private:
    void onBlockUpdatesChanged();

    friend class QQmlWebChannelPrivate;
    friend class QWebChannel;
    friend class TestWebChannel;
    friend class ::tst_bench_QWebChannel;

    QWebChannel *webChannel;
    std::unordered_map<const QThread*, SignalHandler<QMetaObjectPublisher>> signalHandlers;
    SignalHandler<QMetaObjectPublisher> *signalHandlerFor(const QObject *object);

    struct TransportState
    {
        TransportState() : clientIsIdle(false) { }
        // true when the client is idle, false otherwise
        bool clientIsIdle;
        // messages to send
        QQueue<QJsonObject> queuedMessages;
    };
    QHash<QWebChannelAbstractTransport *, TransportState> transportState;

    // true when no property updates should be sent, false otherwise
    Q_OBJECT_BINDABLE_PROPERTY(QMetaObjectPublisher, bool, blockUpdatesStatus);

    QPropertyChangeHandler<std::function<void()>> blockUpdatesHandler;
    // true when at least one client was initialized and thus
    // the property updates have been initialized and the
    // object info map set.
    bool propertyUpdatesInitialized;

    // The update interval in ms when more than zero.
    // Update in next event loop when zero.
    // Update immediately when less than zero.
    Q_OBJECT_BINDABLE_PROPERTY(QMetaObjectPublisher, int, propertyUpdateIntervalTime);

    QPropertyChangeHandler<std::function<void()>> propertyUpdateIntervalHandler;
    // Map of registered objects indexed by their id.
    QHash<QString, QObject *> registeredObjects;

    // Map the registered objects to their id.
    QHash<const QObject *, QString> registeredObjectIds;

    // Groups individually wrapped objects with their class information and the transports that have access to it.
    // Also tags objects that are in the process of being wrapped to prevent infinite recursion.
    struct ObjectInfo
    {
        ObjectInfo(QObject *o = nullptr)
            : object(o), isBeingWrapped(false)
        {}
        QObject *object;
        QList<QWebChannelAbstractTransport *> transports;
        bool isBeingWrapped;
    };

    // Map of objects wrapped from invocation returns
    QHash<QString, ObjectInfo> wrappedObjects;
    // Map of transports to wrapped object ids
    QMultiHash<QWebChannelAbstractTransport*, QString> transportedWrappedObjects;

    // Map of objects to maps of signal indices to a set of all their property indices.
    // The last value is a set as a signal can be the notify signal of multiple properties.
    typedef QHash<int, QSet<int> > SignalToPropertyNameMap;
    QHash<const QObject *, SignalToPropertyNameMap> signalToPropertyMap;

    // Keeps property observers alive for as long as we track an object
    std::unordered_multimap<const QObject*, QWebChannelPropertyChangeNotifier> propertyObservers;

    // Objects that changed their properties and are waiting for idle client.
    typedef QHash<int, QVariantList> SignalToArgumentsMap;

    // A set of plain property index (for bindable properties) and a map of
    // signal index to arguments (for property updates from a notify signal).
    // NOTIFY signals and their arguments are first collected and then mapped to
    // the corresponding property in sendPendingPropertyUpdates()
    struct PropertyUpdate
    {
    public:
        SignalToArgumentsMap signalMap;
        QSet<int> plainProperties;

        /**
         * Given a SignalToPropertyNameMap, returns the set of all property
         * indices of properties that were changed in this PropertyUpdate.
         */
        QSet<int> propertyIndices(const SignalToPropertyNameMap &map) const;
    };

    // map of object to either a property index for plain bindable properties
    // or a to map of signal index to arguments
    typedef QHash<const QObject *, PropertyUpdate> PendingPropertyUpdates;
    PendingPropertyUpdates pendingPropertyUpdates;

    // Aggregate property updates since we get multiple Qt.idle message when we have multiple
    // clients. They all share the same QWebProcess though so we must take special care to
    // prevent message flooding.
    QBasicTimer timer;
};

inline QSet<int> QMetaObjectPublisher::PropertyUpdate::propertyIndices(const SignalToPropertyNameMap &map) const {
    auto indexes = plainProperties;
    for (auto it = signalMap.cbegin(); it != signalMap.cend(); ++it) {
        indexes += map.value(it.key());
    }
    return indexes;
}

QT_END_NAMESPACE

#endif // QMETAOBJECTPUBLISHER_P_H
