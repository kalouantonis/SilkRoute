#include "suppliertable.h"

// Debugging
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

SupplierTable::SupplierTable(QObject* parent)
    : DB::ITableModel(parent)
{
    // Load default settings for table model

    // Default load up query
    SelectAll();

    // Set header data
    this->setHeaderData(ID, Qt::Horizontal, QObject::tr("Ref"));
    this->setHeaderData(NAME, Qt::Horizontal, QObject::tr("Name"));
    this->setHeaderData(PROFIT, Qt::Horizontal, QObject::tr("Profit"));
    this->setHeaderData(EXPENDITURE, Qt::Horizontal, QObject::tr("Expenditure"));
    // Allow clicking to open transaction window
    this->setHeaderData(LAST_TRANSACTION, Qt::Horizontal, QObject::tr("Last Transaction"));
}

void SupplierTable::SelectAll()
{
    // Select everything from table
    this->setQuery("SELECT * FROM suppliers");
}

void SupplierTable::Search(const QString &term)
{
    this->setQuery("SELECT * FROM suppliers WHERE id LIKE \"%" + term + "%\" OR name LIKE \"%" + term + "%\"");

#ifdef _DEBUG
    qDebug() << "Query made: " + this->query().lastQuery() +
                "\n\tFound " + QString::number(this->rowCount()) + " rows" +
                "\n\tErrors: " << GetLastError();
#endif
}

