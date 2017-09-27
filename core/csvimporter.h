#ifndef CSVIMPORTER_H
#define CSVIMPORTER_H

#include "iimporter.h"
#include <QStringList>
#include <QObject>

class CORESHARED_EXPORT CsvImporter : public QObject, public IImporter
{
    Q_OBJECT

public:
    explicit CsvImporter(const QMetaObject *metaObject, QObject *parent = NULL);

    // IImporter interface
public:
    void setImportFile(const QString &fileName);
    int recordCount();
    QSharedPointer<QObject> nextRecord();
    bool isError();

    void setSeparator(const QString &separator);

signals:
    void parseError();
    void noSuchProperty(QString propName);

private:
    void parseFile();

    QString m_header;
    QString m_separator;
    QString m_fileName;
    QStringList m_lines;
    bool m_parsed;
    bool m_error;
    int m_currentRec;
};

#endif // CSVIMPORTER_H
