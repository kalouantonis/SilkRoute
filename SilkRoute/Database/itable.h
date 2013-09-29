#ifndef ITABLE_H
#define ITABLE_H

#include <QObject>
#include <Qt/qstring.h>
#include <QSqlQuery>
#include <QSqlError>

namespace DB
{
    class ITable : public QObject
    {
        Q_OBJECT
    public:
        ITable(QObject *parent = 0);
        virtual ~ITable();

        const QString GetLastError();

        // Checks if query is sanitized, stopping (MOST) SQL Injections
        static QString SanitizeQuery(const QString& str);

    signals:

    public slots:

    protected:
        // Clear SQL Query class
        void m_ClearQuery();

        // Empty query class
        QSqlQuery m_qry;

    };
}

#endif // ITABLE_H
