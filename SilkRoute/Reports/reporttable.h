#ifndef REPORTTABLE_H
#define REPORTTABLE_H

#include <QDate>

#include <SilkRoute/Database/itablemodel.h>

/// Table representing report data gathered from database
class ReportTable: public DB::ITableModel
{
public:
    /// Constructor, takes parent object
    ReportTable(QObject* parent = nullptr);

    /// Data container definition, containing data gathered
    /// from queries
    typedef struct Data
    {
        QDate fromDate;     /// Date to generate report from
        QDate toDate;       /// Date to generate report to
        bool daily;         /// Is report a daily one
    } Data;

    /// Data container to represent value sums from database.
    typedef struct Sums
    {
        double revenue;     // Total revenue
        double cost;        // Total cost
        double profit;      // Total profit
    } Sums;

    /// Columns that are used in the table
    enum COLUMNS
    {
        DESCRIPTION,    /// Type description
        STOCK_REF,      /// Stock item reference
        REVENUE,        /// Revenue from transactions
        COST,           /// Cost of stock item
        PROFIT,         /// Profit gained from stock item
        SUPPLIER_NAME   /// Name of supplier
    };

    /// Select relevant items given specified data as arguments
    /// and add them to model to be displayed
    void Select(const Data& data);
    /// Get sum of revenue, cost and profit given certain arguments
    Sums GetSums(const Data& data);

    /// Inherited method, set as blank. The functionality is not required
    virtual void SelectAll() override {}
    /// Inherited method, set as blank. The functionality is not required
    virtual void Search(const QString &) override {}

protected:
    /// Will not return anything, should not be called. Will cause a segfault.
    virtual const QString &tableName() const { }

private:
    /// Used for logging
    const static QString TAG;
};

#endif // REPORTTABLE_H
