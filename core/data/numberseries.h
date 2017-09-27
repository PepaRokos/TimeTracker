#ifndef NUMBERSERIES_H
#define NUMBERSERIES_H

#include <QObject>
#include <QSharedPointer>

#include <odb/core.hxx>

#include "season.h"
#include "core_global.h"

#pragma db object
class CORESHARED_EXPORT NumberSeries : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix)
    Q_PROPERTY(int lastNumber READ lastNumber WRITE setLastNumber)
    Q_PROPERTY(QString pluginName READ pluginName)
    Q_PROPERTY(QString seasonName READ seasonName)
public:
    explicit NumberSeries(QObject *parent = 0);

    int id() const;
    void setId(int id);

    QString prefix() const;
    void setPrefix(const QString &prefix);

    int lastNumber() const;
    void setLastNumber(int lastNumber);

    QString pluginId() const;
    void setPluginId(const QString &pluginId);

    QSharedPointer<Season> season() const;
    void setSeason(const QSharedPointer<Season> &season);

    QString seasonName() const;

    QString pluginName() const;

private:
    friend class odb::access;

#pragma db id auto
    int m_id;
    QString m_prefix;
    int m_lastNumber;
    QString m_pluginId;
    QSharedPointer<Season> m_season;
};

typedef QSharedPointer<NumberSeries> NumberSeriesPtr;

#endif // NUMBERSERIES_H
