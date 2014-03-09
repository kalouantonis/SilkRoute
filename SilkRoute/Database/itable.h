#ifndef ITABLE_H
#define ITABLE_H

#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>

#include <QRegExp>
#include <QRegExpValidator>

namespace DB
{
    /// Class describing a database table
    class ITable : public QObject
    {
        Q_OBJECT
    public:
        /// Constructor, declaring a parent class
        explicit ITable(QObject *parent = 0);
        /// Destructor
        virtual ~ITable();

        /// Get last error from database
        const QString GetLastError();

    protected:
        /// Clear SQL Query class
        void m_ClearQuery();

        /// SQL abstraction class to make queries with
        QSqlQuery m_qry;

    };
}

#endif // ITABLE_H
