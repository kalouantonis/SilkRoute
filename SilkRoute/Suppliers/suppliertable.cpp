#include "suppliertable.h"

// Debugging
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlIndex>

#include <SilkRoute/Database/dbutils.h>
#include <SilkRoute/Utils/Logger.h>
#include <SilkRoute/Base/itemreferencedexception.h>

// Set static values
const QString SupplierTable::m_internalTableName = "suppliers";
const QString SupplierTable::TAG = "SupplierTable";

const QString SupplierTable::m_selectStatement =
    /// Select supplier name and primary key id
    "SELECT id, name, "
        /// Calculate profit for each supplier
        "(SELECT (SUM( "
                /// Check that transactions are larger than 0
                "CASE WHEN (transactions.no_sold > 0) "
                    /// If so, set revenue value to 0
                    "THEN 0 "
                    /// Otherwise calculate the correct revenue amount
                    "ELSE (transactions.amount*transactions.no_sold*-1) "
                "END"
            /// Subtract costs
            ") - "
            /// Get absolute value of number sold and calculate total costs
            "SUM(ABS(transactions.no_sold)*stock.local_price)"
        ") "
        /// Get data from transaction_stock table
         "FROM transaction_stock "
        /// Join transactions table on to transaction_stock table
         "LEFT JOIN transactions ON transaction_id=transactions.id, "
            /// Join stock table on to transaction_stock table
             "stock ON stock_id=stock.id "
        /// Only select items where the stock ID matches the given expression
         "WHERE stock_id=( "
              /// Get the stock ID from the stock table
              "SELECT stock.id FROM stock "
                /// Only where the supplier foreign key in the stock table
                /// matches the supplier primary key and where the stock item
                /// is not marked as deleted
               "WHERE stock.supplier_id=suppliers.id AND stock.deleted=0"
          /// Only select items where the transaction is not deleted
          ") AND transactions.deleted=0) AS profit "
    /// Get the rest of the data from the suppliers table
    /// and only select suppliers that are not marked as deleted
    "FROM suppliers WHERE suppliers.deleted=0 ";


SupplierTable::SupplierTable(QObject* parent)
    : DB::ITableModel(parent)
{
    // Set sql table name
    this->setTable(m_internalTableName);
    // Declare primary key column
    this->setPrimaryKey(QSqlIndex("id"));
    // Load all data
    SelectAll();

    // Load horizontal header data with specified names
    this->setHeaderData(ID, Qt::Horizontal, QObject::tr("Ref"));
    this->setHeaderData(NAME, Qt::Horizontal, QObject::tr("Name"));
    this->setHeaderData(PROFIT, Qt::Horizontal, QObject::tr("Profit"));
}

void SupplierTable::Search(const QString &term)
{
    // Set query to be used by model. Use default select query along with
    // extra filters to narrow down results according to search term
    this->setQuery(QSqlQuery(m_selectStatement + "AND suppliers.id LIKE \"%" + term +
                             "\" OR suppliers.name LIKE \"%" + term + "\"%"));

    // Log query data to console
    debug(TAG, "Query made: " + this->query().lastQuery() +
                "n\tErrors: " + this->GetLastError());
}

void SupplierTable::SelectAll()
{
    // Send default query to model
    this->setQuery(QSqlQuery(m_selectStatement));

    // Log query data to console
    debug(TAG, "Query made: " + this->query().lastQuery() +
                "n\tErrors: " + this->GetLastError());
}


bool SupplierTable::Insert(const Data &data)
{
    // Create query for inserting a supplier.
    QSqlQuery& qry = DB::PrepareQuery(
                /// Insert data in to supplier table
                "INSERT INTO " + m_internalTableName +
                /// Insert in to name and deleted columns
                " (name,  deleted) "
                /// Set the values to the binded amounts
                "VALUES (:name, 0)"
    );

    // bind supplier name in to query
    qry.bindValue(":name", data.name);

    // Check if query failed
    if(!qry.exec())
    {
        // Log error to console
        debug(TAG, "Query failed: " + qry.lastQuery() +
              "\n\t" + GetLastError());

        // Query failed
        return false;
    }

    // Log to console
    debug(TAG, "Query made: " + qry.lastQuery());

    // Send data changed signal, refresh query
    emit dataChanged();

    // Query succeeded
    return true;
}

bool SupplierTable::Update(const Data &data)
{
    // Create query for updating existing suppliers.
    QSqlQuery& qry = DB::PrepareQuery(
                /// Update the stock table
                "UPDATE " + m_internalTableName +
                /// Set the name column value
                " SET name=:name"
                /// Where the ID matches the binded ID
                " WHERE id=:id");

    // Bind values to query using the data provided as a function argument
    qry.bindValue(":name", data.name);
    qry.bindValue(":id", data.id);


    // Exec query
    if(!qry.exec())
    {
        // Log error to console
        debug(TAG, "Query failed: " + qry.lastQuery() +
              "\n\t" + GetLastError());

        // query failed
        return false;
    }

    // Log to console
    debug(TAG, "Query made: " + qry.lastQuery());

    // Notify model of data change
    emit dataChanged();

    // Query success
    return true;
}

bool SupplierTable::Remove(int id)
{
    // Create query to find any items under
    QSqlQuery& qry = DB::PrepareQuery(
                "SELECT supplier_id FROM stock "
                "WHERE supplier_id=:id"
    );

    // bind id value to given ID in function parameter
    qry.bindValue(":id", id);

    // Exec query
    if(!qry.exec())
    {
        // Log error to console
        debug(TAG, "Query failed: " + qry.lastQuery() +
              "\n\t" + GetLastError());

        // Query failed
        return false;
    }

    // Log to console
    debug(TAG, "Query made: " + qry.lastQuery());

    // Check if item exists
    if(qry.next())
    {
        // If already exists, throw exception
        throw ItemReferencedException();
    }

    // Create query for deleteting a supplier under a given ID
    qry = DB::PrepareQuery("UPDATE " + tableName() +
                           " SET deleted=1 "
                           " WHERE id=:id");

    // Bind id value to query
    qry.bindValue(":id", id);

    // Did query fail?
    if(!qry.exec())
    {
        // Log error to console
        debug(TAG, "Query failed: " + qry.lastQuery() +
              "\n\t" + GetLastError());

        // Query failed
        return false;
    }

    // Log to console
    debug(TAG, "Query made: " + qry.lastQuery());

    // Notify model of data change
    emit dataChanged();

    // Query succeeded
    return true;
}

void SupplierTable::sort(int column, Qt::SortOrder order)
{
    // Get standard select statement and add grouping operator
    QString queryString = m_selectStatement + " ORDER BY ";

    // Get related column that is requested for sort. Simply add the
    // required SQL column id on to the current query string
    if(column == ID)
        queryString += "suppliers.id";
    else if(column == NAME)
        queryString += "suppliers.name";
    else if(column == PROFIT)
        queryString += "amount";
    else
        // exit function
        return;

    // Check order requested for sort and specify the related SQL operator
    if(order == Qt::AscendingOrder)
        queryString += " ASC";
    else
        queryString += " DESC";

    // Send the query to the model for displaying
    this->setQuery(QSqlQuery(queryString));

    // Log query to console with any errors (if they exist)
    debug(TAG, "Query made: " + this->query().lastQuery()
          + "\n\tErrors: " + GetLastError());
}


