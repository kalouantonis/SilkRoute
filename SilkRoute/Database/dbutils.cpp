#include "dbutils.h"

#include <QRegExp>

#include <QFile>
#include <QTextStream>

#include <cassert>

namespace DB
{

bool CreateAllTables(const QString& filename)
{
    // File stream for schema
    QFile schema_file;

    schema_file.setFileName(filename);
    if(!schema_file.open(QFile::ReadOnly))
    {
        qDebug() << schema_file.errorString();

        return false;
    }

    // SQL Query to be performed
    QSqlQuery qry;

    // Create text stream for file data
    QTextStream dataStream(&schema_file);

    // Temporary storage for whole stream data
    QString tmpData;

    for(QString line = dataStream.readLine(); !line.isNull(); line = dataStream.readLine())
    {
        tmpData += line;

        if(line.contains(';'))
        {
            // Add statement to qry
            qry.prepare(tmpData);

#ifdef _DEBUG
            // This will slow down execution alot, so only use in debug mode
            qDebug() << "Executing query: " << tmpData;
#endif

            tmpData.clear();
        }
    }


    // Close open file stream
    schema_file.close();

    // Execute the query
    if(!qry.exec())
    {
        qDebug() << qry.lastError();

        return false;
    }


    return true;
}


QRegExpValidator* GetAlNumValidator(QObject *parent)
{
    // Allow alphanum characters and whitespace at the end of expression
    return new QRegExpValidator(QRegExp("[A-Za-z0-9_]*$+"), parent);
}

QRegExpValidator* GetNumericValidator(QObject *parent)
{
    // Allow numeric characters only
    return new QRegExpValidator(QRegExp("[0-9. ]*$+"), parent);
}

}
