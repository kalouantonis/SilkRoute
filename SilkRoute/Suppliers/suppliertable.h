#ifndef SUPPLIERTABLE_H
#define SUPPLIERTABLE_H

#include <SilkRoute/Database/itablemodel.h>

class SupplierTable: public DB::ITableModel
{
public:
    SupplierTable(QObject* parent = 0);


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
};

#endif // SUPPLIERTABLE_H
