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

    QRegExpValidator* ITable::GetAlNumValidator(QObject* parent)
    {
        //QRegExp re("[A-Za-z0-9]", Qt::CaseInsensitive);
        return new QRegExpValidator(QRegExp("[A-Za-z0-9]+"), parent);
    }

    ITable::~ITable()
    {

    }
}
