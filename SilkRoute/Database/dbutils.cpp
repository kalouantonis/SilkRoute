#include "dbutils.h"

bool CreateAllTables()
{
    QSqlQuery qry;
    qry.prepare("CREATE TABLE IF NOT EXISTS users"
                "(id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT, admin INTEGER)");

    qry.prepare("CREATE TABLE IF NOT EXISTS \"main\".\"suppliers\" ("
                "\"id\" INTEGER PRIMARY KEY AUTOINCREMENT,"
                "\"name\" TEXT,"
                "\"profit\" REAL,"
                "\"expenditure\" REAL,"
                "\"last_transaction\" INTEGER"
                ");");


    if(!qry.exec())
    {
        qDebug() << qry.lastError();

        return false;
    }


    return true;
}
