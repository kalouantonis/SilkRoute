#include <SilkRoute/Utils/Logger.h>
#include <SilkRoute/Database/dbutils.h>
#include "typestable.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

#include <SilkRoute/Base/itemreferencedexception.h>


const QString TypesTable::internalTableName = "types";
const QString TypesTable::TAG = "TypesTable";

TypesTable::TypesTable(QObject* parent)
    : DB::ITableModel(parent)
{
    this->setTable(internalTableName);
    SelectAll();

    //this->removeColumn(ID);
    this->removeColumn(DELETED);
    this->setHeaderData(REF, Qt::Horizontal, QObject::tr("Ref"));
    this->setHeaderData(DESCRIPTION, Qt::Horizontal, QObject::tr("Description"));
}


void TypesTable::Search(const QString &term)
{
   setFilter("deleted=0 AND (ref LIKE \"%" + term +
       "%\" OR description LIKE \"%" + term + "%\")");

    debug(TAG, "Query made: " + this->query().lastQuery() +
          "\n\tFound: " + QString::number(this->rowCount()));
}

bool TypesTable::RefExists(const QString &ref)
{
    QSqlQuery qry = this->query();

    qry.prepare("SELECT * FROM " + internalTableName + " WHERE ref= :ref"
                " AND deleted=0");
    qry.bindValue(":ref", ref);

    //this->setQuery(qry);

    if(!qry.exec())
    {
        debug(TAG, "Failed to execute query: " + qry.lastError().text());
        // Fix this maybe?
        throw std::runtime_error("Failed to execute query: " + qry.lastError().text().toStdString());
    }

    debug(TAG, "Query made: " + qry.lastQuery());

    if(!qry.next())
    {
        debug(TAG, "No results found for: " + ref);

        return false;
    }

    debug(TAG, "Found " + QString::number(qry.size()) + " results");

    return true;
}

bool TypesTable::Insert(const TypesTable::Data &data)
{
    QSqlQuery qry = this->query();
    qry.prepare("INSERT INTO " + internalTableName + " (ref, description, deleted) " +
                "VALUES (:ref, :desc, 0)");

    qry.bindValue(":ref", data.ref);
    qry.bindValue(":desc", data.description);

    if(!qry.exec())
    {
        debug("Query failed: " + qry.lastQuery() + "\n\tError: " + qry.lastError().text());

        return false;
    }

    debug(TAG, "Query made: " + qry.lastQuery());

    emit this->dataChanged();

    return true;
}

bool TypesTable::Update(const TypesTable::Data &data)
{
    QSqlQuery qry = this->query();
    qry.prepare("UPDATE " + internalTableName + " SET description=:desc"
                " WHERE id=:id");

    qry.bindValue(":desc", data.description);
    qry.bindValue(":id", data.id);

    if(!qry.exec())
    {
        error(TAG, "Query failed: " + qry.lastQuery() +
              "\n\t" + qry.lastError().text());

        return false;
    }

    emit this->dataChanged();

    return true;
}

bool TypesTable::Remove(int id)
{
     QSqlQuery& qry = DB::PrepareQuery("SELECT type_id FROM stock "
                                      "WHERE type_id=:id");

    qry.bindValue(":id", id);


    // Exec query
    if(!qry.exec())
    {
        error(TAG, "Query failed: " + qry.lastQuery() +
              "\n\t" + qry.lastError().text());

        return false;
    }

    if(qry.next())
    {
        throw ItemReferencedException();
    }

    qry = DB::PrepareQuery("UPDATE " + tableName() +
                           " SET deleted=1 "
                           " WHERE id=:id");

    qry.bindValue(":id", id);

    if(!qry.exec())
    {

        error(TAG, "Query failed: " + qry.lastQuery() +
              "\n\t" + qry.lastError().text());
        return false;
    }

    emit dataChanged();

    return true;

}
