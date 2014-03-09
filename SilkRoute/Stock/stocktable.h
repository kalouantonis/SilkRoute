#ifndef STOCKTABLE_H
#define STOCKTABLE_H

#include <SilkRoute/Database/itablemodel.h>
#include <SilkRoute/Database/itablemodel.h>

/// Represents stock table data
class StockTable: public DB::ITableModel
{
    Q_OBJECT

public:
    /// Constructor, takes parent object
    StockTable(QObject* parent = 0);

    /// Data container definition, containing data gathered
    /// from queries
    typedef struct Data
    {
        int id;                 /// Stock item ID
        QString ref;            /// Stock item reference text
        int supplier_id;        /// supplier foreign key
        int type_id;            /// type foreign key
        double foreign_price;   /// foreign price of stock item
        float exchange_rate;    /// exchange rate used for item
        double local_price;     /// local price of item
    } Data;

    /// Columns that are used in the table
    enum STOCK_COLUMNS
    {
        ID,             /// Primary key column
        REF ,           /// Stock reference
        SUPPLIER,       /// Supplier ID foreign key
        TYPE,           /// Type ID foreign key
        FOREIGN_PRICE,  /// Foreign price of stock item
        EXCHANGE_RATE,  /// exchange rate used for item
        LOCAL_PRICE,    /// items local price
        NUM_STOCK,      /// No. of items in stock
        DELETED         /// Marks stock items as deleted or not
    };

    /// Search data in database using a given term
    virtual void Search(const QString& term) final;

    /// Insert new data in to table
    /// Returns false if query failed
    bool Insert(const Data& data);
    /// Update existing table data.
    /// Returns false if query failed
    bool Update(const Data& data);

    /// Select all items from table
    virtual void SelectAll() override;
    /// Select data for given id
    Data Select(int id);

    /// Remove item from database using the given ID
    /// Returns false if query failed
    virtual bool Remove(int id) final;

    /// Called by model when sorting of data is requested
    /// Gives the column requested for sorting and weather it is
    /// ascending or descending
    virtual void sort(int column, Qt::SortOrder order);

protected:
    /// Get name of database table used by this class
    virtual const QString& tableName() const override { return m_internalTableName; }

private:
    /// Database table used internaly by this class
    const static QString m_internalTableName;
    /// Used for logging
    const static QString TAG;

    /// Default sql select statement used
    const static QString m_selectStatement;
};

#endif // STOCKTABLE_H
