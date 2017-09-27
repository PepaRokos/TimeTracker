#include "report.h"

Report::Report()
{

}

QString Report::name() const
{
    return m_name;
}

void Report::setName(const QString &name)
{
    m_name = name;
}

QString Report::description() const
{
    return m_description;
}

void Report::setDescription(const QString &description)
{
    m_description = description;
}

QString Report::file() const
{
    return m_file;
}

void Report::setFile(const QString &file)
{
    m_file = file;
}

bool Report::listReport() const
{
    return m_listReport;
}

void Report::setListReport(bool listReport)
{
    m_listReport = listReport;
}

QMap<QString, QString> Report::variables() const
{
    return m_variables;
}

void Report::setVariables(const QMap<QString, QString> &variables)
{
    m_variables = variables;
}

void Report::setVariable(const QString &varName, const QString &value)
{
    m_variables[varName] = value;
}
