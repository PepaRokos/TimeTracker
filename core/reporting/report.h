#ifndef REPORT_H
#define REPORT_H

#include <QString>
#include <QMap>
#include <QList>
#include <QSharedPointer>

#include "../core_global.h"

class CORESHARED_EXPORT Report
{
public:
    Report();

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    QString file() const;
    void setFile(const QString &file);

    bool listReport() const;
    void setListReport(bool listReport);

    QMap<QString, QString> variables() const;
    void setVariables(const QMap<QString, QString> &variables);
    void setVariable(const QString &varName, const QString &value);

private:
    QString m_name;
    QString m_description;
    QString m_file;
    bool m_listReport;
    QMap<QString, QString> m_variables;
};

typedef QSharedPointer<Report> ReportPtr;
typedef QList<ReportPtr> ReportList;

#endif // REPORT_H
