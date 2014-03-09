#include "reporttable.h"

#include <SilkRoute/Database/dbutils.h>
#include <SilkRoute/Transactions/transactiontable.h>
#include <SilkRoute/Utils/Logger.h>

#include <QSqlQuery>
#include <QSqlError>


const QString ReportTable::TAG = "ReportTable";

ReportTable::ReportTable(QObject *parent)
    : ITableModel(parent)
{
}

void ReportTable::Select(const ReportTable::Data &data)
{
    /// Query used for selecting data
    QString queryString =
            /// Select type description and stock reference
            "SELECT types.description, stock.ref, "
            /// Select revenue using the given calculation
            /// If the number of items sold is larger than 0, then it is a cost
            /// and revenue gained is set to 0
            "(CASE WHEN (transactions.no_sold > 0) "
                "THEN 0 "
                "ELSE (transactions.amount*transactions.no_sold*-1) "
            "END) AS revenue, "
            /// Select cost using the given calculation
            "(ABS(transactions.no_sold)*stock.local_price) AS cost, "
            /// Select profit using the given calculation using revenue and costs.
            "("
                "(CASE WHEN (transactions.no_sold > 0) "
                    "THEN 0 "
                    "ELSE (transactions.amount*transactions.no_sold*-1) "
                "END) - "
                "(ABS(transactions.no_sold)*stock.local_price)"
            ") AS profit, "
            /// Select supplier name
            "suppliers.name "
            /// Get data from transaction_stock table
            "FROM transaction_stock "
            /// Join transaction table on to transaction_stock table
            /// where transaction_id matches the transaction primary key
            "LEFT JOIN transactions ON transaction_id=transactions.id, "
            /// Join stock table on to transaction_stock table where
            /// its stock_id matches the stock table primary key
            "stock ON stock_id=stock.id, "
            /// Join suppliers table on to stock table where
            /// its supplier_id matches the suppliers table primary key
            "suppliers ON supplier_id=suppliers.id, "
            /// Join types table on to stock table where
            /// its types_id foreign key matches the suppliers table primary key
            "types ON type_id=types.id "
            /// Only select items that are not marked as deleted
            "WHERE transactions.deleted=0 ";

    // Check if report is daily
    if(data.daily)
    {
        // Only select a single transaction date
        queryString += "AND trans_date=" +
                // Convert date to date format used in table
                data.fromDate.toString(TransactionTable::dateFormat());
    }
    else // Report is not daily
    {
        // Select transaction dates between the from and to given values
        queryString += "AND (transaction_stock.trans_date BETWEEN " +
                data.fromDate.toString(TransactionTable::dateFormat()) +
                " AND " + data.toDate.toString(TransactionTable::dateFormat())
                + ")";
    }

    // create query and send to model
    this->setQuery(QSqlQuery(queryString));

    // log query and errors (if any) to console
    debug(TAG, "Query made: " + this->query().lastQuery()
          + "\n\tErrors: " + GetLastError());

    // Reload horizontal header data with specified names
    this->setHeaderData(DESCRIPTION, Qt::Horizontal, QObject::tr("Description"));
    this->setHeaderData(STOCK_REF, Qt::Horizontal, QObject::tr("Stock Ref."));
    this->setHeaderData(REVENUE, Qt::Horizontal, QObject::tr("Revenue"));
    this->setHeaderData(COST, Qt::Horizontal, QObject::tr("Cost"));
    this->setHeaderData(PROFIT, Qt::Horizontal, QObject::tr("Profit"));
    this->setHeaderData(SUPPLIER_NAME, Qt::Horizontal, QObject::tr("Supplier Name"));
}

ReportTable::Sums ReportTable::GetSums(const ReportTable::Data &data)
{
    QString queryString =
            /// Initiate select query
            "SELECT "
            /// Get sum of revenues using the calculation given below
            "SUM( "
                "(CASE WHEN (transactions.no_sold > 0) "
                     "THEN 0 "
                     "ELSE (transactions.amount*transactions.no_sold*-1) "
                "END)"
            ") AS revenue, "
            /// Get the sum of costs
            "SUM(ABS(transactions.no_sold)*stock.local_price) AS cost, "
            /// Calculate the profit using cost and revenue sums
            "("
                "SUM( "
                    /// If the number sold in transaction is larger than 0
                    /// set revenue to 0
                    "CASE WHEN (transactions.no_sold > 0) "
                        "THEN 0 "
                        "ELSE (transactions.amount*transactions.no_sold*-1) "
                    "END"
                ") - "
                "SUM(ABS(transactions.no_sold)*stock.local_price)"
            ") AS profit "
            /// Select from transaction_stock table
            "FROM transaction_stock "
            /// Join transactions table on to transaction_stock table
            /// where its transaction_id foreign key is equal to the
            /// transaction table primary key
            "LEFT JOIN transactions ON transaction_id=transactions.id, "
            /// Join stock table on to transaction_stock table
            /// where its stock_id foreign key matches the
            /// stock table primary key
            "stock ON stock_id=stock.id "
            /// Only select items not marked as deleted
            "WHERE transactions.deleted=0 ";

    // If report is not daily
    if(!data.daily)
    {
        // Create query selecting transactions with dates between the
        // given values
        queryString += "AND (transaction_stock.trans_date BETWEEN "
                // Convert to internal database date format
                + data.fromDate.toString(TransactionTable::dateFormat())
                + " AND " + data.toDate.toString(TransactionTable::dateFormat())
                + ")";
    }
    else // report is daily
    {
        // Only select a single transaction date
        queryString += "AND transaction_stock.trans_date="
                + data.fromDate.toString(TransactionTable::dateFormat());
    }

    // Create and prepare new query using the given query string
    QSqlQuery& qry = DB::PrepareQuery(queryString);

    // Create empty sums table, initializing the data as -1 for validation
    Sums sums { -1, -1, -1 };

    // Did the query fail?
    if(!qry.exec())
    {
        // Log to console
        debug(TAG, "Query failed: " + qry.lastQuery()
              + "\n\tError: " + qry.lastError().text());
    }
    else
    {
        // Log query to console
        debug(TAG, "Query succeeded: " + qry.lastQuery());

        // Select first item. Should only have 1
        qry.next();

        // select revenue column and convert to double
        sums.revenue = qry.value("revenue").toDouble();
        // select cost column and convert to double
        sums.cost = qry.value("cost").toDouble();
        // select profit column and convert to double
        sums.profit = qry.value("profit").toDouble();
    }

    // return sums to caller
    return sums;
}
