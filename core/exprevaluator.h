#ifndef EXPREVALUATOR_H
#define EXPREVALUATOR_H

#include <QMap>
#include <QString>
#include <QVariant>
#include <functional>

#include "core_global.h"

class CORESHARED_EXPORT ExprEvaluator
{
public:
    ExprEvaluator();

    bool evaluate(QObject *object, const QString &exp);
    void setCaseSensitive(bool caseSensitive);

private:
#ifdef _MSC_VER
    QMap<QString, std::function<bool(QVariant, QVariant)> > m_operations;
#else
    static const QMap<QString, std::function<bool(QVariant, QVariant)> > m_operations;
#endif

    bool m_caseSensitive;

    bool subEval(const QString &oper, const QString &expresion, QObject *object);
    void parseExpr(const QString &exp, QVariant &value, QString &oper, QVariant &condition, QObject *object);
};

#endif // EXPREVALUATOR_H
