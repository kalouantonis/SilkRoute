#ifndef SUPPLIERTABLE_H
#define SUPPLIERTABLE_H

#include <SilkRoute/Database/itablemodel.h>

class SupplierTable: public DB::ITableModel
{
public:
    SupplierTable(QObject* parent = 0);

    // Used for transferring all supplier data
    typedef struct SupplierData
    {
           int id;
           QString name;
           double profit;
           double expenditure;
           int last_transaction;
    } SupplierData;


    // TODO: Move to suppliertable
    // Provides enums for column access, keep stuff simple
    enum SUP_COLUMNS
    {
        ID,
        NAME,
        PROFIT,
        EXPENDITURE,
        LAST_TRANSACTION
    };

    // Select all from table
    virtual void SelectAll() final;

    virtual void Search(const QString& term) final;

    // Will return false if query failed
    bool Insert(const SupplierData& data);

    bool Update(const SupplierData& data);

    bool Remove(int id);
};

#endif // SUPPLIERTABLE_H
