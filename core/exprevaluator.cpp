#include "exprevaluator.h"

#ifdef _MSC_VER
ExprEvaluator::ExprEvaluator()
{
    m_operations["=="] = [](QVariant left, QVariant right) { return left == right; };
    m_operations["!="] = [](QVariant left, QVariant right) { return left != right; };
    m_operations["<"] = [](QVariant left, QVariant right) { return left < right; };
    m_operations["<="] = [](QVariant left, QVariant right) { return left <= right; };
    m_operations[">"] = [](QVariant left, QVariant right) { return left > right; };
    m_operations[">="] = [](QVariant left, QVariant right) { return left >= right; };
    m_operations["%"] = [](QVariant left, QVariant right) { return left.toString().contains(right.toString()); };

    m_operations["||"] = [](QVariant left, QVariant right) { return left.toBool() || right.toBool(); };
    m_operations["&&"] = [](QVariant left, QVariant right) { return left.toBool() && right.toBool(); };
    m_caseSensitive = false;
}
#else
const QMap<QString, std::function<bool(QVariant, QVariant)> > ExprEvaluator::m_operations = {
    { "==", [](QVariant left, QVariant right) { return left == right; }},
    { "!=", [](QVariant left, QVariant right) { return left != right; }},
    { "<",  [](QVariant left, QVariant right) { return left < right; }},
    { "<=", [](QVariant left, QVariant right) { return left <= right; }},
    { ">",  [](QVariant left, QVariant right) { return left > right; }},
    { ">=", [](QVariant left, QVariant right) { return left >= right; }},
    { "%", [](QVariant left, QVariant right) { return left.toString().contains(right.toString()); }},

    { "||", [](QVariant left, QVariant right) { return left.toBool() || right.toBool(); }},
    { "&&", [](QVariant left, QVariant right) { return left.toBool() && right.toBool(); }}
};

ExprEvaluator::ExprEvaluator()
{
    m_caseSensitive = false;
}
#endif


bool ExprEvaluator::evaluate(QObject *object, const QString &exp)
{
    if (exp.contains("&&") && exp.contains("||"))
    {
        if (exp.indexOf("&&") < exp.indexOf("||"))
        {
            return subEval("&&", exp, object);
        }
        else
        {
            return subEval("||", exp, object);
        }
    }
    else if (exp.contains("&&"))
    {
        return subEval("&&", exp, object);
    }
    else if (exp.contains("||"))
    {
        return subEval("||", exp, object);
    }
    else
    {
        QVariant value;
        QString oper;
        QVariant cond;
        parseExpr(exp, value, oper, cond, object);

        if (cond.isValid())
        {
            return m_operations[oper](value, cond);
        }

        return true;
    }
}

void ExprEvaluator::setCaseSensitive(bool caseSensitive)
{
    m_caseSensitive = caseSensitive;
}

bool ExprEvaluator::subEval(const QString &oper, const QString &expresion, QObject *object)
{
    QString ex = expresion.left(expresion.indexOf(oper));
    QVariant value;
    QString o;
    QVariant cond;
    parseExpr(ex, value, o, cond, object);
    return m_operations[oper](m_operations[o](value, cond), evaluate(object, expresion.mid(expresion.indexOf(oper) + 2).trimmed()));
}

void ExprEvaluator::parseExpr(const QString &exp, QVariant &value, QString &oper, QVariant &condition, QObject *object)
{
    QStringList expCat = exp.trimmed().split(" ");
    value = object->property(expCat[0].toStdString().c_str());
    oper = expCat[1];

    if (expCat.size() > 2)
    {
        condition = expCat[2].replace("%20", " ");
    }
}

