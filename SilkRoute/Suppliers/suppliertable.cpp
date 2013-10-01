#include "suppliertable.h"

SupplierTable::SupplierTable(QObject* parent)
    : QSqlQueryModel(parent)
{
    // Load default settings for table model

    // Default load up query
    this->setQuery("SELECT * FROM suppliers");

    // Set header data
    this->setHeaderData(ID, Qt::Horizontal, QObject::tr("Ref"));
    this->setHeaderData(NAME, Qt::Horizontal, QObject::tr("Name"));
    this->setHeaderData(PROFIT, Qt::Horizontal, QObject::tr("Profit"));
    this->setHeaderData(EXPENDITURE, Qt::Horizontal, QObject::tr("Expenditure"));
    // Allow clicking to open transaction window
    this->setHeaderData(LAST_TRANSACTION, Qt::Horizontal, QObject::tr("Last Transaction"));
}
