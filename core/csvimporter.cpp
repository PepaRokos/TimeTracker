#include "csvimporter.h"
#include <QFile>
#include <QVariant>

CsvImporter::CsvImporter(const QMetaObject *metaObject, QObject *parent)
    :QObject(parent),
     IImporter(metaObject)
{
    m_parsed = false;
    m_currentRec = 1;
    m_error = false;
}

void CsvImporter::setImportFile(const QString &fileName)
{
    m_fileName = fileName;
}

int CsvImporter::recordCount()
{
    if (!m_parsed)
    {
        parseFile();
    }

    return m_lines.count() - 1;
}

QSharedPointer<QObject> CsvImporter::nextRecord()
{
    if (!m_parsed)
    {
        parseFile();
    }

    QObject *entity = m_metaObject->newInstance();

    if (entity == NULL || m_currentRec > recordCount())
    {
        ++m_currentRec;
        return QSharedPointer<QObject>();
    }

    QStringList props = m_header.split(m_separator);
    QString line = m_lines[m_currentRec];
    QStringList values = line.split(m_separator);

    for (int i = 0; i < props.size(); i++) {
        QString property = props[i];
        QString value = values[i];
        if (!entity->setProperty(property.toStdString().c_str(), QVariant(value)))
        {
            m_error = true;
            emit noSuchProperty(property);

            ++m_currentRec;
            return QSharedPointer<QObject>();
        }
    }

    ++m_currentRec;

    return QSharedPointer<QObject>(entity);
}

bool CsvImporter::isError()
{
    return m_error;
}

void CsvImporter::parseFile()
{
    QFile file(m_fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        m_error = true;
        emit parseError();
        return;
    }

    QByteArray data = file.readAll();
    QString strData(data);

    m_lines = strData.split("\n");
    m_header = m_lines[0];
    m_parsed = true;
}

void CsvImporter::setSeparator(const QString &separator)
{
    m_separator = separator;
}
