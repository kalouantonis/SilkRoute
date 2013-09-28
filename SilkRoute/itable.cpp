#include "itable.h"

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

    ITable::~ITable()
    {

    }
}
