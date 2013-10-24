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
        // Instruct query to finish processing
        m_qry.finish();

        // Clear data
        m_qry.clear();
    }

    ITable::~ITable()
    {

    }
}
