#ifndef ITABLE_H
#define ITABLE_H

#include <QObject>
#include <Qt/qstring.h>
#include <QSqlQuery>
#include <QSqlError>

#include <QRegExp>
#include <QRegExpValidator>

namespace DB
{
    class ITable : public QObject
    {
        Q_OBJECT
    public:
        explicit ITable(QObject *parent = 0);
        virtual ~ITable();

        const QString GetLastError();


    protected:
        // Clear SQL Query class
        void m_ClearQuery();

        // Empty query class
        QSqlQuery m_qry;

    };
}

#endif // ITABLE_H
