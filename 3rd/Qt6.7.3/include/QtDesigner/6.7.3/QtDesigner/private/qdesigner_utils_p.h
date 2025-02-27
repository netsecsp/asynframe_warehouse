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

#ifndef QDESIGNER_UTILS_H
#define QDESIGNER_UTILS_H

#include "shared_global_p.h"

#include <QtDesigner/abstractformwindow.h>

#include <QtCore/qcompare.h>
#include <QtCore/qhash.h>
#include <QtCore/qvariant.h>
#include <QtCore/qshareddata.h>
#include <QtWidgets/qmainwindow.h>
#include <QtGui/qicon.h>
#include <QtGui/qpixmap.h>

#include <map>

QT_BEGIN_NAMESPACE

class QDebug;

namespace qdesigner_internal {
class QDesignerFormWindowCommand;
class DesignerIconCache;
class FormWindowBase;


QDESIGNER_SHARED_EXPORT QString dataDirectory();

QDESIGNER_SHARED_EXPORT QString legacyDataDirectory();

QDESIGNER_SHARED_EXPORT void designerWarning(const QString &message);

QDESIGNER_SHARED_EXPORT void reloadIconResources(DesignerIconCache *iconCache, QObject *object);

/* Flag/Enumeration helpers for the property sheet: Enumeration or flag values are returned by the property sheet
 * as a pair of meta type and integer value.
 * The meta type carries all the information required for the property editor and serialization
 * by the form builders (names, etc).
 * Note that the property editor uses unqualified names ("Cancel") while the form builder serialization  (uic)
 * requires the whole string
 * ("QDialogButtonBox::Cancel" or "org.qt-project.qt.gui.QDialogButtonBox.StandardButton.Cancel").*/

/* --------- MetaEnum: Base class representing a QMetaEnum with lookup functions
 * in both ways. Template of int type since unsigned is more suitable for flags.
 * The keyToValue() is ignorant of scopes, it can handle fully qualified or unqualified names. */

template <class IntType>
class MetaEnum
{
public:
    enum SerializationMode { FullyQualified,
                             Qualified }; // Qt pre 6.7 without enum name

    using KeyToValueMap = std::map<QString, IntType, std::less<>>;

    MetaEnum(const QString &enumName, const QString &scope, const QString &separator);
    MetaEnum() = default;
    void addKey(IntType value, const QString &name);

    QString valueToKey(IntType value, bool *ok = nullptr) const;
    // Ignorant of scopes.
    IntType keyToValue(QStringView key, bool *ok = nullptr) const;

    const QString &enumName() const  { return m_enumName; }
    const QString &scope() const     { return m_scope; }
    const QString &separator() const { return m_separator; }

    const QStringList &keys() const { return m_keys; }
    const KeyToValueMap &keyToValueMap() const { return m_keyToValueMap; }

protected:
    void appendQualifiedName(const QString &key, SerializationMode sm, QString &target) const;

private:
    QString m_enumName;
    QString m_scope;
    QString m_separator;
    KeyToValueMap m_keyToValueMap;
    QStringList m_keys;
};

template <class IntType>
MetaEnum<IntType>::MetaEnum(const QString &enumName, const QString &scope, const QString &separator) :
      m_enumName(enumName),
    m_scope(scope),
    m_separator(separator)
{
}

template <class IntType>
void MetaEnum<IntType>::addKey(IntType value, const QString &name)
{
    m_keyToValueMap.insert({name, value});
    m_keys.append(name);
}

template <class IntType>
QString MetaEnum<IntType>::valueToKey(IntType value, bool *ok) const
{
    QString rc;
    for (auto it = m_keyToValueMap.begin(), end = m_keyToValueMap.end(); it != end; ++it)  {
        if (it->second == value) {
            rc = it->first;
            break;
        }
    }
    if (ok)
        *ok = !rc.isEmpty();
    return rc;
}

template <class IntType>
IntType MetaEnum<IntType>::keyToValue(QStringView key, bool *ok) const
{
    const auto lastSep = key.lastIndexOf(m_separator);
    if (lastSep != -1)
        key = key.sliced(lastSep + m_separator.size());
    const auto it = m_keyToValueMap.find(key);
    const bool found = it != m_keyToValueMap.end();
    if (ok)
        *ok = found;
    return found ? it->second : IntType(0);
}

template <class IntType>
void MetaEnum<IntType>::appendQualifiedName(const QString &key, SerializationMode sm,
                                            QString &target) const
{
    if (!m_scope.isEmpty()) {
        target += m_scope;
        target += m_separator;
    }
    if (sm == FullyQualified)
        target += m_enumName + m_separator;
    target += key;
}

// -------------- DesignerMetaEnum: Meta type for enumerations

class QDESIGNER_SHARED_EXPORT DesignerMetaEnum : public MetaEnum<int>
{
public:
    DesignerMetaEnum(const QString &name, const QString &scope, const QString &separator);
    DesignerMetaEnum() = default;

    QString toString(int value, SerializationMode sm, bool *ok = nullptr) const;

    QString messageToStringFailed(int value) const;
    QString messageParseFailed(const QString &s) const;

    // parse a string (ignorant of scopes)
    int parseEnum(const QString &s, bool *ok = nullptr) const { return keyToValue(s, ok); }
};

// -------------- DesignerMetaFlags: Meta type for flags.
// Note that while the handling of flags is done using unsigned integers, the actual values returned
// by the property system  are integers.

class QDESIGNER_SHARED_EXPORT DesignerMetaFlags : public MetaEnum<uint>
{
public:
    explicit DesignerMetaFlags(const QString &enumName, const QString &scope,
                               const QString &separator);
    DesignerMetaFlags() = default;

    QString toString(int value, SerializationMode sm) const;
    QStringList flags(int value) const;

    QString messageParseFailed(const QString &s) const;
    // parse a string (ignorant of scopes)
    int parseFlags(const QString &s, bool *ok = nullptr) const;
};

// -------------- EnumValue: Returned by the property sheet for enumerations

struct QDESIGNER_SHARED_EXPORT PropertySheetEnumValue
{
    PropertySheetEnumValue(int v, const DesignerMetaEnum &me);
    PropertySheetEnumValue();

    int value{0};
    DesignerMetaEnum metaEnum;
};

// -------------- FlagValue: Returned by the property sheet for flags

struct QDESIGNER_SHARED_EXPORT PropertySheetFlagValue
{
    PropertySheetFlagValue(int v, const DesignerMetaFlags &mf);
    PropertySheetFlagValue();

    int value{0};
    DesignerMetaFlags metaFlags;
};

// -------------- PixmapValue: Returned by the property sheet for pixmaps
class QDESIGNER_SHARED_EXPORT PropertySheetPixmapValue
{
public:
    PropertySheetPixmapValue(const QString &path);
    PropertySheetPixmapValue();

    // Check where a pixmap comes from
    enum PixmapSource { LanguageResourcePixmap , ResourcePixmap, FilePixmap };
    static PixmapSource getPixmapSource(QDesignerFormEditorInterface *core, const QString & path);

    PixmapSource pixmapSource(QDesignerFormEditorInterface *core) const { return getPixmapSource(core, m_path); }

    QString path() const;
    void setPath(const QString &path); // passing the empty path resets the pixmap

private:
    friend size_t qHash(const PropertySheetPixmapValue &p, size_t seed = 0) noexcept
    {
        return qHash(p.m_path, seed);
    }
    friend bool comparesEqual(const PropertySheetPixmapValue &lhs,
                              const PropertySheetPixmapValue &rhs) noexcept
    {
        return lhs.m_path == rhs.m_path;
    }
    Q_DECLARE_EQUALITY_COMPARABLE(PropertySheetPixmapValue)

    QString m_path;
};

// -------------- IconValue: Returned by the property sheet for icons

class PropertySheetIconValueData;

class QDESIGNER_SHARED_EXPORT PropertySheetIconValue
{
 public:
    explicit PropertySheetIconValue(const PropertySheetPixmapValue &pixmap);
    PropertySheetIconValue();
    ~PropertySheetIconValue();
    PropertySheetIconValue(const PropertySheetIconValue &) noexcept;
    PropertySheetIconValue &operator=(const PropertySheetIconValue &);
    PropertySheetIconValue(PropertySheetIconValue &&) noexcept;
    PropertySheetIconValue &operator=(PropertySheetIconValue &&) noexcept;

    bool isEmpty() const;

    QString theme() const;
    void setTheme(const QString &);

    int themeEnum() const;
    void setThemeEnum(int e);

    PropertySheetPixmapValue pixmap(QIcon::Mode mode, QIcon::State state) const;
    void setPixmap(QIcon::Mode mode, QIcon::State state, const PropertySheetPixmapValue &path); // passing the empty path resets the pixmap

    uint mask() const;
    uint compare(const PropertySheetIconValue &other) const;
    void assign(const PropertySheetIconValue &other, uint mask);

    // Convenience accessors to get themed/unthemed icons.
    PropertySheetIconValue themed() const;
    PropertySheetIconValue unthemed() const;

    using ModeStateKey = std::pair<QIcon::Mode, QIcon::State>;
    using ModeStateToPixmapMap = QMap<ModeStateKey, PropertySheetPixmapValue>;

    const ModeStateToPixmapMap &paths() const;

private:
    friend QDESIGNER_SHARED_EXPORT
    size_t qHash(const PropertySheetIconValue &p, size_t seed) noexcept;
    friend size_t qHash(const PropertySheetIconValue &p) noexcept
    { return qHash(p, 0); }
    friend QDESIGNER_SHARED_EXPORT
    bool comparesEqual(const PropertySheetIconValue &lhs,
                       const PropertySheetIconValue &rhs) noexcept;
    Q_DECLARE_EQUALITY_COMPARABLE(PropertySheetIconValue)

    QSharedDataPointer<PropertySheetIconValueData> m_data;
};

QDESIGNER_SHARED_EXPORT QDebug operator<<(QDebug, const PropertySheetIconValue &);

class QDESIGNER_SHARED_EXPORT DesignerPixmapCache : public QObject
{
    Q_OBJECT
public:
    DesignerPixmapCache(QObject *parent = nullptr);
    QPixmap pixmap(const PropertySheetPixmapValue &value) const;
    void clear();
signals:
    void reloaded();
private:
    mutable QHash<PropertySheetPixmapValue, QPixmap> m_cache;
    friend class FormWindowBase;
};

class QDESIGNER_SHARED_EXPORT DesignerIconCache : public QObject
{
    Q_OBJECT
public:
    explicit DesignerIconCache(DesignerPixmapCache *pixmapCache, QObject *parent = nullptr);
    QIcon icon(const PropertySheetIconValue &value) const;
    void clear();
signals:
    void reloaded();
private:
    mutable QHash<PropertySheetIconValue, QIcon> m_cache;
    DesignerPixmapCache *m_pixmapCache;
    friend class FormWindowBase;
};

// -------------- PropertySheetTranslatableData: Base class for translatable properties.
class QDESIGNER_SHARED_EXPORT PropertySheetTranslatableData
{
protected:
    PropertySheetTranslatableData(bool translatable = true,
                                  const QString &disambiguation = QString(),
                                  const QString &comment = QString());

public:
    bool translatable() const                { return m_translatable; }
    void setTranslatable(bool translatable)  { m_translatable = translatable; }
    QString disambiguation() const           { return m_disambiguation; }
    void setDisambiguation(const QString &d) { m_disambiguation = d; }
    QString comment() const                  { return m_comment; }
    void setComment(const QString &comment)  { m_comment = comment; }
    QString id() const                       { return m_id; }
    void setId(const QString &id)            { m_id = id; }

private:
    friend bool comparesEqual(const PropertySheetTranslatableData &lhs,
                              const PropertySheetTranslatableData &rhs) noexcept
    {
        return lhs.m_translatable == rhs.m_translatable
            && lhs.m_disambiguation == rhs.m_disambiguation
            && lhs.m_comment == rhs.m_comment
            && lhs.m_id == rhs.m_id;
    }
    Q_DECLARE_EQUALITY_COMPARABLE(PropertySheetTranslatableData)

    bool m_translatable;
    QString m_disambiguation;
    QString m_comment;
    QString m_id;
};

// -------------- StringValue: Returned by the property sheet for strings
class QDESIGNER_SHARED_EXPORT PropertySheetStringValue : public PropertySheetTranslatableData
{
public:
    PropertySheetStringValue(const QString &value = QString(), bool translatable = true,
                             const QString &disambiguation = QString(), const QString &comment = QString());

    QString value() const;
    void setValue(const QString &value);

private:
    friend bool comparesEqual(const PropertySheetStringValue &lhs,
                              const PropertySheetStringValue &rhs) noexcept
    {
        const PropertySheetTranslatableData &upLhs = lhs;
        const PropertySheetTranslatableData &upRhs = rhs;
        return lhs.m_value == rhs.m_value && upLhs == upRhs;
    }
    Q_DECLARE_EQUALITY_COMPARABLE(PropertySheetStringValue)

    QString m_value;
};

// -------------- StringValue: Returned by the property sheet for string lists
class QDESIGNER_SHARED_EXPORT PropertySheetStringListValue : public PropertySheetTranslatableData
{
public:
    PropertySheetStringListValue(const QStringList &value = QStringList(),
                                 bool translatable = true,
                                 const QString &disambiguation = QString(),
                                 const QString &comment = QString());

    QStringList value() const;
    void setValue(const QStringList &value);

private:
    friend bool comparesEqual(const PropertySheetStringListValue &lhs,
                              const PropertySheetStringListValue &rhs) noexcept
    {
        const PropertySheetTranslatableData &upLhs = lhs;
        const PropertySheetTranslatableData &upRhs = rhs;
        return lhs.m_value == rhs.m_value && upLhs == upRhs;
    }
    Q_DECLARE_EQUALITY_COMPARABLE(PropertySheetStringListValue)

    QStringList m_value;
};

// -------------- StringValue: Returned by the property sheet for strings
class QDESIGNER_SHARED_EXPORT PropertySheetKeySequenceValue : public PropertySheetTranslatableData
{
public:
    PropertySheetKeySequenceValue(const QKeySequence &value = QKeySequence(),
                                  bool translatable = true,
                                  const QString &disambiguation = QString(),
                                  const QString &comment = QString());
    PropertySheetKeySequenceValue(const QKeySequence::StandardKey &standardKey,
                                  bool translatable = true,
                                  const QString &disambiguation = QString(),
                                  const QString &comment = QString());

    QKeySequence value() const;
    void setValue(const QKeySequence &value);
    QKeySequence::StandardKey standardKey() const;
    void setStandardKey(const QKeySequence::StandardKey &standardKey);
    bool isStandardKey() const;

private:
    friend bool comparesEqual(const PropertySheetKeySequenceValue &lhs,
                              const PropertySheetKeySequenceValue &rhs) noexcept
    {
        const PropertySheetTranslatableData &upLhs = lhs;
        const PropertySheetTranslatableData &upRhs = rhs;
        return lhs.m_value == rhs.m_value && lhs.m_standardKey == rhs.m_standardKey
            && upLhs == upRhs;
    }
    Q_DECLARE_EQUALITY_COMPARABLE(PropertySheetKeySequenceValue)

    QKeySequence m_value;
    QKeySequence::StandardKey m_standardKey;
};

} // namespace qdesigner_internal

QT_END_NAMESPACE


// NOTE: Do not move this code, needed for GCC 3.3
Q_DECLARE_METATYPE(qdesigner_internal::PropertySheetEnumValue)
Q_DECLARE_METATYPE(qdesigner_internal::PropertySheetFlagValue)
Q_DECLARE_METATYPE(qdesigner_internal::PropertySheetPixmapValue)
Q_DECLARE_METATYPE(qdesigner_internal::PropertySheetIconValue)
Q_DECLARE_METATYPE(qdesigner_internal::PropertySheetStringValue)
Q_DECLARE_METATYPE(qdesigner_internal::PropertySheetStringListValue)
Q_DECLARE_METATYPE(qdesigner_internal::PropertySheetKeySequenceValue)


QT_BEGIN_NAMESPACE

namespace qdesigner_internal {


// Create a command to change a text property (that is, create a reset property command if the text is empty)
QDESIGNER_SHARED_EXPORT QDesignerFormWindowCommand *createTextPropertyCommand(const QString &propertyName, const QString &text, QObject *object, QDesignerFormWindowInterface *fw);

// Returns preferred task menu action for managed widget
QDESIGNER_SHARED_EXPORT QAction *preferredEditAction(QDesignerFormEditorInterface *core, QWidget *managedWidget);

enum class UicLanguage
{
    Cpp,
    Python,
};

// Convenience to run UIC
QDESIGNER_SHARED_EXPORT bool runUIC(const QString &fileName, UicLanguage language,
                                    QByteArray& ba, QString &errorMessage);

// Find a suitable variable name for a class.
QDESIGNER_SHARED_EXPORT QString qtify(const QString &name);

/* UpdateBlocker: Blocks the updates of the widget passed on while in scope.
 * Does nothing if the incoming widget already has updatesEnabled==false
 * which is important to avoid side-effects when putting it into QStackedLayout. */

class QDESIGNER_SHARED_EXPORT UpdateBlocker {
    Q_DISABLE_COPY_MOVE(UpdateBlocker)

public:
    UpdateBlocker(QWidget *w);
    ~UpdateBlocker();

private:
    QWidget *m_widget;
    const bool m_enabled;
};

// QPalette helpers: Mask for a single color role/group
QDESIGNER_SHARED_EXPORT quint64 paletteResolveMask(QPalette::ColorGroup colorGroup,
                                                   QPalette::ColorRole colorRole);
// Mask for the colors of a role in all groups (Active/Inactive/Disabled)
QDESIGNER_SHARED_EXPORT quint64 paletteResolveMask(QPalette::ColorRole colorRole);

namespace Utils {

inline int valueOf(const QVariant &value, bool *ok = nullptr)
{
    if (value.canConvert<PropertySheetEnumValue>()) {
        if (ok)
            *ok = true;
        return qvariant_cast<PropertySheetEnumValue>(value).value;
    }
    if (value.canConvert<PropertySheetFlagValue>()) {
        if (ok)
            *ok = true;
        return qvariant_cast<PropertySheetFlagValue>(value).value;
    }
    return value.toInt(ok);
}

inline bool isObjectAncestorOf(QObject *ancestor, QObject *child)
{
    QObject *obj = child;
    while (obj != nullptr) {
        if (obj == ancestor)
            return true;
        obj = obj->parent();
    }
    return false;
}

inline bool isCentralWidget(QDesignerFormWindowInterface *fw, QWidget *widget)
{
    if (! fw || ! widget)
        return false;

    if (widget == fw->mainContainer())
        return true;

    // ### generalize for other containers
    if (QMainWindow *mw = qobject_cast<QMainWindow*>(fw->mainContainer())) {
        return mw->centralWidget() == widget;
    }

    return false;
}

} // namespace Utils

} // namespace qdesigner_internal

QT_END_NAMESPACE

#endif // QDESIGNER_UTILS_H
