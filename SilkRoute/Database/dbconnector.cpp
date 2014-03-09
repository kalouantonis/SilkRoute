#include "dbconnector.h"
#include <QDebug>

// For error handeling
#include <QSqlError>
#include <SilkRoute/Utils/Logger.h>


namespace DB
{
    const QString DBConnector::TAG = "DBConnector";

    DBConnector::DBConnector()
        : m_db(QSqlDatabase::addDatabase("QSQLITE")) // Construct database driver
    {

    }

    int DBConnector::connect(const QString &filename)
    {
        // Check if database is open
        if(m_db.isOpen())
        {
           // Connection already exists
            debug(TAG, "DB driver is already initialized");

            // Return to caller, giving the information that the
            // connection already exists
            return CON_EXISTS;
        }

        // Connect to host locally, may do this externally for
        // networking
        m_db.setDatabaseName(filename);

        // Check if connection to database succeeded
        if(!m_db.open())
        {
            // Log error to console
            error(TAG, "Connection to " + filename + " database failed" +
                  "\n\t" + m_db.lastError().text());

            // return Connection failed value to caller
            return CON_FAILED;
        }


        if(!m_db.isValid())
        {
            error(TAG, filename + " is corrupted");

            return CON_INVALID;
        }

        // Log message to console
        debug(TAG, "Connection to " + filename + " succeeded");

        // Return connection success value to caller
        return CON_SUCCESS;
    }

    void DBConnector::close()
    {
        // Close database connection
        m_db.close();
    }
}
