#include "itablemodel.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

#include <SilkRoute/Utils/Logger.h>
#include <SilkRoute/Database/dbutils.h>

namespace DB
{

const QString ITableModel::TAG = "ITableModel";

ITableModel::ITableModel(QObject* parent)
    : QSqlTableModel(parent) // Parent constructor
{
    // Connect signature of dataChanged() signal to the relevant function
    // to update all table data
    this->connect(this, SIGNAL(dataChanged()), this, SLOT(updateAllData()));
}

void ITableModel::SelectAll()
{
    // Select everything, excluding deleted items
    this->setFilter("deleted=0");
    // Select data from sql. Internally calls SELECT statement
    this->select();
}

bool ITableModel::Remove(int id)
{
    // Create new query
    QSqlQuery qry = DB::PrepareQuery("UPDATE " + tableName() + " SET deleted=1"
                " WHERE id=:id");

    // Bind the id value to the :id field declared in the query
    qry.bindValue(":id", id);

    if(!qry.exec())
    {
        // Log to console
        debug(TAG, "Error removing record.\n\tQuery:"
                    + qry.lastQuery()
                    + GetLastError());

        // Return to false to caller, signifying a failed query
        return false;
    }

    // log to console
    debug(TAG, "Query made: " + qry.lastQuery());

    // Send signal that data in the table was changed
    emit this->dataChanged();

    // query success
    return true;
}

}
