#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QSqlDatabase>

namespace DB
{
    /// Different return types for connector
    enum CONNECTOR_REC
    {
        CON_SUCCESS,    // DB Connected successfully
        CON_FAILED,     // Failed to connect
        CON_EXISTS,     // Connection already exists
        CON_INVALID     // Invalid database file
    };

    /// Class that represents the connection to the database
    class DBConnector
    {
    private:
        /// Used for logging
        const static QString TAG;

        /// Actual database connection
        QSqlDatabase m_db;
    public:
        /// Initlize DB with default SQLite driver
        DBConnector();
        /// Close connection when destructor is called
        ~DBConnector() { close(); }

        /// Make connection to database
        int connect(const QString& filename);

        /// Close database connection
        void close(void);
    };
}

#endif // DBCONNECTOR_H
