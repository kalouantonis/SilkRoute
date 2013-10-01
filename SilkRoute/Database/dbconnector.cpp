#include "dbconnector.h"
#include <QDebug>

// For error handeling
#include <QSqlError>

namespace DB
{
    DBConnector::DBConnector()
        : m_db(QSqlDatabase::addDatabase("QSQLITE"))
    {

    }

    int DBConnector::connect(const QString &filename)
    {
        if(m_db.isOpen())
        {
           // Connection already exists
#ifdef _DEBUG
            qDebug() << "DB driver is already initialized";
#endif

            return CON_EXISTS;
        }

        // Connect to host locally, may do this externally for
        // networking
        //m_db.setHostName("localhost");
        m_db.setDatabaseName(filename);

        //m_db.setUserName("user");
        //m_db.setPassword("password");

        if(!m_db.open())
        {
#ifdef _DEBUG
            qDebug() << "Connection to " << filename <<" database failed";
            qDebug() << m_db.lastError();
#endif

            return CON_FAILED;
        }

#ifdef _DEBUG
        qDebug() << "Connection to " << filename << " succeeded!\n";
#endif

        return CON_SUCCESS;
    }

    void DBConnector::close()
    {
        m_db.close();
    }
}
