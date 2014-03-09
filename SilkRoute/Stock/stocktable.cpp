#include "stocktable.h"

#include <QSqlQuery>
#include <QSqlIndex>
#include <QSqlRelation>

#include <SilkRoute/Utils/Logger.h>
#include <SilkRoute/Suppliers/suppliertable.h>
#include <SilkRoute/Database/dbutils.h>
#include <SilkRoute/Base/itemreferencedexception.h>

// Set static values
const QString StockTable::m_internalTableName = "stock";
const QString StockTable::TAG = "StockTable";

const QString StockTable::m_selectStatement =
        "SELECT stock.id, stock.ref, "      /// Select stock item id and reference
        "suppliers.name, types.ref"         /// Select supplier name and type reference
        ", foreign_price "                  /// Select foreign price
        ", exchange_rate, local_price, "    /// Select exchange rate and local price

            /// Select the sum of number of items sold from transactions table
            /// by joining the transaction table on to the transaction_stock table
            /// where the transaction_id foreign key matches the transaction primary
            /// key. Get where transaction_stock foreign key of stock_id matches
            /// the given stock ID
            "(SELECT SUM(no_sold) FROM transaction_stock LEFT JOIN "
            "transactions ON transaction_id=transactions.id WHERE "
            "stock_id=stock.id AND transactions.deleted=0) AS no_items "
       /// Get data from stock, suppliers and types table
       "FROM stock, suppliers, types "
       /// Select where the stock supplier foreign key matches the given supplier table
       /// primary key ID and the stock type foreign key matches the given type
       /// table primary key
       "WHERE (stock.\"supplier_id\"=suppliers.id AND stock.type_id=types.id) "
       /// Select all items NOT marked as deleted
       "AND stock.deleted=0";

StockTable::StockTable(QObject* parent)
    : DB::ITableModel(parent)
{
    // Set table name used by the model
    this->setTable(m_internalTableName);
    // Specify the primary key column name
    this->setPrimaryKey(QSqlIndex("id"));
    // Fill model with all data
    SelectAll();

    // Load horizontal header data with specified names
    this->setHeaderData(REF, Qt::Horizontal, QObject::tr("Ref"));
    this->setHeaderData(SUPPLIER, Qt::Horizontal, QObject::tr("Supplier"));
    this->setHeaderData(TYPE, Qt::Horizontal, QObject::tr("Type"));
    this->setHeaderData(FOREIGN_PRICE, Qt::Horizontal, QObject::tr("Foreign Price"));
    this->setHeaderData(EXCHANGE_RATE, Qt::Horizontal, QObject::tr("Exchange Rate (%)"));
    this->setHeaderData(LOCAL_PRICE, Qt::Horizontal, QObject::tr("Local Price"));
    this->setHeaderData(NUM_STOCK, Qt::Horizontal, QObject::tr("No. in Stock"));
}

void StockTable::Search(const QString &term)
{
    // Set query to be used by model. Use default select query along with
    // extra filters to narrow down results according to search term
    this->setQuery(QSqlQuery(m_selectStatement +
                             " AND stock.ref LIKE \"%" + term + "%\""));
}


bool StockTable::Insert(const Data &data)
{
    // Create query for inserting stock items.
    QSqlQuery& qry = DB::PrepareQuery(
                /// Insert in to stock table
                "INSERT INTO " + tableName() +
                    /// Insert in to ref, supplier_id, type_id, foreign_price
                    /// exchange_rate, local_price and deleted fields
                    " (ref, supplier_id, type_id, foreign_price, "
                    "exchange_rate, local_price, deleted)"
                /// Set values as special chars for use when binding afterwards
                " VALUES(:ref, :supplier_id, :type_id, :foreign_price, "
                    /// Set deleted to 0
                    ":exchange_rate, :local_price, 0)"
    );

    // Bind values to query using the data provided as a function argument
    qry.bindValue(":ref", data.ref);
    qry.bindValue(":supplier_id", data.supplier_id);
    qry.bindValue(":type_id", data.type_id);
    qry.bindValue(":foreign_price", data.foreign_price);
    qry.bindValue(":exchange_rate", data.exchange_rate);
    qry.bindValue(":local_price", data.local_price);

    // If query failed
    if(!qry.exec())
    {
        // Log error to console
        debug(TAG, "Query failed: " + qry.lastQuery() +
              "\n\t" + GetLastError());

        // Fail function call
        return false;
    }

    // Log to console
    debug(TAG, "Query made: " + qry.lastQuery());

    // Notify model of data change
    emit dataChanged();

    // Query success
    return true;
}

bool StockTable::Update(const StockTable::Data &data)
{
    // Create query for updating existing stock items.
    QSqlQuery& qry = DB::PrepareQuery(
                /// Update the stock table and set each column values
                /// to the ones being binded below
                "UPDATE " + tableName() + " SET " +
                    "ref=:ref, supplier_id=:sup_id, type_id=:type_id, "
                    "foreign_price=:foreign_price, exchange_rate=:exchange, "
                    "local_price=:local_price "
                /// Only select items with the specified id
                "WHERE id=:id"
    );

    // Bind values to query using the data provided as a function argument
    qry.bindValue(":ref", data.ref);
    qry.bindValue(":sup_id", data.supplier_id);
    qry.bindValue(":type_id", data.type_id);
    qry.bindValue(":foreign_price", data.foreign_price);
    qry.bindValue(":exchange", data.exchange_rate);
    qry.bindValue(":local_price", data.local_price);
    qry.bindValue(":id", data.id);

    // If query failed
    if(!qry.exec())
    {
        // Log error to console
        debug(TAG, "Query failed: " + qry.lastQuery()
              + "\n\tError: " + qry.lastError().text());

        // Query failed
        return false;
    }

    // Notify model of data change
    emit dataChanged();

    // Query success
    return true;
}

void StockTable::SelectAll()
{
    // Send default query to model
    this->setQuery(QSqlQuery(m_selectStatement));

    // Log query to console with any errors (if they exist)
    debug(TAG, "Query made: " + this->query().lastQuery()
          + "\n\tErrors:  " + this->GetLastError());
}

StockTable::Data StockTable::Select(int id)
{
    // Create query for selecting stock data under a given ID
    QSqlQuery& qry = DB::PrepareQuery(
                /// Select all columns from stock table
                "SELECT * FROM stock "
                /// Only where the ID matches the binded ID and
                /// it is not marked as deleted
                "WHERE id=:id AND deleted=0"
    );

    // Bind the ID to the query string
    qry.bindValue(":id", id);

    // Create query data container
    Data data;

    // If query failed
    if(!qry.exec())
    {
        // Log query and errors to console
        debug(TAG, "Query failed: " + qry.lastQuery()
              + "\n\tError: " + qry.lastError().text());

        // Set id to -1 for error checking
        data.id = -1;
        // return invalid data to caller
        return data;
    }


    // Check if item exists in query return
    if(qry.next())
    {
        // Set the data ID to the one given as a function parameter
        data.id = id;
        // Get reference text from ref column
        data.ref = qry.value("ref").toString();
        // Get supplier table foreign key as integer
        data.supplier_id = qry.value("supplier_id").toInt();
        // Get type table foreign key as integer
        data.type_id = qry.value("type_id").toInt();
        // Get foreign price of stock item and convert value to a double
        data.foreign_price = qry.value("foreign_price").toDouble();
        // Get exchange rate of stock item and convert value to a float
        data.exchange_rate = qry.value("exchange_rate").toFloat();
        // Get local price of stock item and convert value to a double
        data.local_price = qry.value("local_price").toDouble();
    }

    // Return data container to caller
    return data;
}

bool StockTable::Remove(int id)
{
    // Create query for deleteting an item under a given ID
    QSqlQuery& qry = DB::PrepareQuery(
                /// Get transaction table primary key
                "SELECT transactions.id "
                "FROM transactions "
                /// Only where it satisfies the given condition
                "WHERE transactions.id=("
                    /// Get transaction foreign key
                    "SELECT transaction_stock.transaction_id "
                    /// From transaction_stock table
                    "FROM transaction_stock "
                    /// Where the transaction_stock table stock foreign key
                    /// matches the binded ID
                    "WHERE transaction_stock.stock_id=:id"
                 ")"
    );

    /// Bind given ID value to query
    qry.bindValue(":id", id);

    // Did query fail?
    if(!qry.exec())
    {
        // Log query and error to console
        debug(TAG, "Query failed: " + qry.lastQuery()
                       + "\n\tError: " + qry.lastError().text());

        // Query failed
        return false;
    }

    // Check if items from query result exist
    if(qry.next())
    {
        // Throw exception, so that caller can catch it
        // Notifies that the item requested to be deleted is already
        // referenced by one or more items
        throw ItemReferencedException();
    }

    // No items reference this one, allow removal

    // Set deleted flag of item to 1, where its primary key matches
    // the binded id
    qry = DB::PrepareQuery("UPDATE " + tableName() +
                           " SET deleted=1 "
                           "WHERE id=:id");
    // Bind ID to query
    qry.bindValue(":id", id);


    // Check success of query
    if(!qry.exec())
    {
        // Log errors to console
        debug(TAG, "Query failed: " + qry.lastQuery()
                       + "\n\tError: " + qry.lastError().text());

        // Query failed
        return false;
    }

    // Notify model of data change
    emit dataChanged();

    // Query succeeded
    return true;
}

void StockTable::sort(int column, Qt::SortOrder order)
{
    // Get standard select statement and add grouping function
    QString query = m_selectStatement + " ORDER BY ";

    // Get related column that is requested for sort. Simply add the
    // required SQL column id on to the current query string
    if(column == REF)
        query += "stock.ref";
    else if(column == SUPPLIER)
        query += "suppliers.name";
    else if(column == TYPE)
        query += "types.ref";
    else if(column == FOREIGN_PRICE)
        query += "stock.foreign_price";
    else if(column == EXCHANGE_RATE)
        query += "stock.exchange_rate";
    else if(column == LOCAL_PRICE)
        query += "stock.local_price";
    else if(column == NUM_STOCK)
        query += "no_items";
    else
        // exit function
        return;

    // Check order requested for sort and specify the related SQL
    // operator
    if(order == Qt::AscendingOrder)
        query += " ASC";
    else
        query += " DESC";

    // Send the query to the model for displaying
    this->setQuery(QSqlQuery(query));

    // Log query to console with any errors (if they exist)
    debug(TAG, "Query made: " + this->query().lastQuery() +
          "\n\tErrors: " + GetLastError());
}
