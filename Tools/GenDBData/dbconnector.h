#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QSqlDatabase>

namespace DB
{
    // Different return types for connector
    enum CONNECTOR_REC
    {
        CON_SUCCESS,    // DB Connected successfully
        CON_FAILED,     // Failed to connect
        CON_EXISTS      // Connection already exists
    };

    class DBConnector
    {
    private:
        // Actual database connection
        QSqlDatabase m_db;
    public:
        // Initlize DB with default SQLite driver
        DBConnector();

        // Make connection to database
        int connect(const QString& filename);

        // Close database connection
        void close(void);
    };
}

#endif // DBCONNECTOR_H
