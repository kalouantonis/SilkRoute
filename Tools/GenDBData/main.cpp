#include <QCoreApplication>

#include "dbconnector.h"
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QSqlError>

#include <QtCore>

const QString encrypt(const char* val)
{
    return QString(QCryptographicHash::hash(val, QCryptographicHash::Sha1).toHex());
}


bool CreateUser(const char* username, const char* password)
{
    QSqlQuery qry;
    qry.prepare("INSERT INTO users (username, password, admin)"
                " VALUES (:user, :pass, :admin)");

    qry.bindValue(":user", encrypt(username));
    qry.bindValue(":pass", encrypt(password));
    qry.bindValue(":admin", 1);

    if(!qry.exec())
    {
        qDebug() << "Query failed in USERS table\n\t"
                    << qry.lastError();
        return false;
    }

    qDebug() << "User Query succeeded";

    return true;
}

int main(int argc, char *argv[])
{
    // Initialize DB
    DB::DBConnector database;
    if(database.connect(argv[1]) == DB::CON_FAILED)
    {
        qFatal("DB Initialization failed");
    }

    CreateUser("user", "word");

    return EXIT_SUCCESS;
}

