#include "itable.h"

// Regular expressions for input sanitization
#include <QRegExp>

#include <QDebug>

namespace DB
{
    ITable::ITable(QObject *parent) :
        QObject(parent)
    {
    }

    const QString ITable::GetLastError()
    {
        return m_qry.lastError().text();
    }

    void ITable::m_ClearQuery()
    {
        m_qry.clear();
    }

    QString ITable::SanitizeQuery(const QString &str)
    {
        //QRegExp re("[A-Za-z0-9]", Qt::CaseInsensitive);
        QRegExp re("[:alnum:]");

        // Escape string, making sure it only has the attributes
        // provided by regex
        //return re.escape(str);
        QString val = re.escape(str);

#ifdef _DEBUG
        qDebug() << "Escaped chars: " + QString::number(re.numCaptures()) +
                    '\n\t' + re.errorString();
#endif

        return val;
    }

    ITable::~ITable()
    {

    }
}
