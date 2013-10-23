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


bool SupplierTable::Insert(const SupplierData &data)
{
    QSqlQuery qry;
    qry.prepare("INSERT INTO suppliers (name, profit, expenditure, last_transaction) VALUES (\":name\", :profit, :expenditure, :last_trans)");

    qry.bindValue(":name", data.name);
    qry.bindValue(":profit", data.profit);
    qry.bindValue(":expenditure", data.expenditure);
    qry.bindValue(":last_trans", data.last_transaction);

    if(!qry.exec())
    {
#ifdef _DEBUG
        qDebug() << "Query failed -- SupplierTable::Insert";
        qDebug() << '\t' << qry.lastError();
        qDebug() << '\t' << qry.lastQuery();
#endif
        return false;
    }

#ifdef _DEBUG
    qDebug() << "Query made: " << qry.lastQuery();
#endif

    return true;
}
