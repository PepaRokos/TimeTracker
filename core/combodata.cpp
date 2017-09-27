#include "combodata.h"

ComboData::ComboData(const QVariant &index, const QString &label)
{
    m_index = index;
    m_label = label;
}

ComboData::ComboData(const QSharedPointer<QObject> &index)
{
    m_index = QVariant::fromValue(index);
    ComboItem *ci = qobject_cast<ComboItem*>(index.data());

    if (ci != NULL)
    {
        m_label = ci->toString();
    }
}

ComboData::~ComboData()
{
}

QVariant ComboData::index() const
{
    return m_index;
}

void ComboData::setIndex(const QVariant &index)
{
    m_index = index;
}

QString ComboData::label() const
{
    return m_label;
}

void ComboData::setLabel(const QString &label)
{
    m_label = label;
}
