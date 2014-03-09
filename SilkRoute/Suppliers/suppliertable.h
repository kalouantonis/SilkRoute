#ifndef SUPPLIERTABLE_H
#define SUPPLIERTABLE_H

#include <SilkRoute/Database/itablemodel.h>

class SupplierTable: public DB::ITableModel
{
    Q_OBJECT

public:
    /// Constructor, takes parent object
    SupplierTable(QObject* parent = 0);

    /// Used for transferring all supplier data
    typedef struct Data
    {
           int id;          /// The suppliers primary key
           QString name;    /// Supplier name
    } Data;


    /// Columns that are used in the table
    enum SUP_COLUMNS
    {
        ID = 0,     /// The primary key field
        NAME,       /// The name of the supplier
        PROFIT,
        DELETED
    };

    /// Search data in database using a given term
    virtual void Search(const QString& term) final;
    /// Select all items from table
    virtual void SelectAll() override;

    /// Insert new data in to table
    /// Returns false if query failed
    bool Insert(const Data& data);

    /// Update existing table data.
    /// Returns false if query failed
    bool Update(const Data& data);

    /// Remove item from database using the given ID
    /// Returns false if query failed
    virtual bool Remove(int id) override;

    /// Called by model when sorting of data is requested
    /// Gives the column requested for sorting and weather it is
    /// ascending or descending
    virtual void sort(int column, Qt::SortOrder order);

private:
    /// Database table used internaly by this class
    static const QString m_internalTableName;
    /// Used for logging
    static const QString TAG;

    /// Sql SELECT statement used for selecting and displaying data
    /// in table view
    static const QString m_selectStatement;

protected:
    /// Get name of database table used by this class
    virtual const QString& tableName() const override { return m_internalTableName; }
};

#endif // SUPPLIERTABLE_H
