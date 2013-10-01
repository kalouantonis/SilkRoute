#ifndef SUPPLIERTABLE_H
#define SUPPLIERTABLE_H

#include <QSqlQueryModel>

class SupplierTable: public QSqlQueryModel
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
    void SelectAll();

    void Search(const QString& term);
};

#endif // SUPPLIERTABLE_H