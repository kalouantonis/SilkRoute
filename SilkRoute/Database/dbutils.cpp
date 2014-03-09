#include "dbutils.h"

#include <QRegExp>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QSqlRecord>

#include <SilkRoute/Utils/Logger.h>

namespace DB
{

bool CreateAllTables(const QString& filename)
{
    // File stream for schema
    QFile schema_file;

    // Set file to parse
    schema_file.setFileName(filename);

    // Check if opening file succeeded
    if(!schema_file.open(QFile::ReadOnly))
    {
        // Error message to console
        error("DB::CreateAllTables",
              "Could not open schema file: " + schema_file.errorString());

        // Return false for failure
        return false;
    }

    // SQL Query to be performed
    QSqlQuery qry;


    // Create text stream for file data
    QTextStream dataStream(&schema_file);

    // Temporary storage for whole stream data
    QString tmpData;

    // Iterate through each line in schema
    for(QString line = dataStream.readLine(); !line.isNull(); line = dataStream.readLine())
    {
        // Append the current line to temporary data store
        tmpData += line;

        // If the end of line has a ';' character
        if(line.endsWith(';'))
        {
            // Execute query using temporary data store and
            // check if query execution was a success
            if(!qry.exec(tmpData))
            {
                // Log error to console
                error("DB::CreateAllTables", "Failed to create DB: " +
                      qry.lastError().text());

                // Return false for failure
                return false;
            }

            // Log message to console
            debug("DB::CreateAllTables", "Executing query: " + tmpData);

            // Clear previous temporary data store
            tmpData.clear();
        }
    }


    // Close open file stream
    schema_file.close();

    // Return true for success
    return true;
}


QRegExpValidator* GetAlNumValidator(QObject *parent)
{
    // Allow alphanum characters and whitespace at the end of expression
    return new QRegExpValidator(QRegExp("[A-Za-z0-9_ ]*$+"), parent);
}

QRegExpValidator* GetNumericValidator(QObject *parent)
{
    // Allow numeric characters only
    return new QRegExpValidator(QRegExp("[0-9.-]*$+"), parent);
}

QRegExpValidator *GetNonNegativeNumericValidator(QObject *parent)
{
    // Allow numeric characters only and no negative signs
    return new QRegExpValidator(QRegExp("[0-9.]*$+"), parent);
}

QSqlQuery &PrepareQuery(const QString &query)
{
    // Create static container using strings as keys and sql queries
    // as values. This reduces execution time if query is used multiple
    // times, as it is only prepared once
    static QMap<QString, QSqlQuery> queries;

    // Check if query string is contained as key withing the container
    if(!queries.contains(query))
    {
         // not found, insert the query in the map and prepare it for execution
        queries[query].prepare(query);
    }

    // Return prepared sql query
    return queries[query];
}

int GetViewIndex(int modelIndex, const QSqlQueryModel *model)
{
    // Set view index to -1 for use in validation routines
    int view_index = -1;

    // Iterate through each row.
    for(int i = 0; i < model->rowCount(); ++i)
    {
        // Get model id index of current record
        int index = model->record(i).value("id").toInt();

        // Check if index corresponds to stock id we are searching for
        if(index == modelIndex)
        {
            // Set view index using the current row index
            view_index = i;
            // Break from the loop, we found what we wanted
            break;
        }
    }

    // return found view index to caller
    return view_index;
}

}
