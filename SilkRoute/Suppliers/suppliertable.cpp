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
                "\n\tFound: " + QString::number(this->rowCount()) +
                '\n\tErrors: ' + this->GetLastError();
#endif
}


bool SupplierTable::Insert(const SupplierData &data)
{
    /*
    this->setQuery("INSERT INTO suppliers (name, profit, expenditure, last_transaction) VALUES ('" + data.name
                  + "', " + QString::number(data.profit) + ", " + QString::number(data.expenditure)
                  + ", " + QString::number(data.last_transaction) + ")");*/

    QSqlQuery qry = this->query();
    qry.prepare("INSERT INTO suppliers (name, profit, expenditure, last_transaction) "
                "VALUES (:name, :profit, :expenditure, :last_trans)");

    qry.bindValue(":name", data.name);
    qry.bindValue(":profit", data.profit);
    qry.bindValue(":expenditure", data.expenditure);
    qry.bindValue(":last_trans", data.last_transaction);

    this->setQuery(qry);

    if(!qry.exec())
    {
#ifdef _DEBUG
        qDebug() << "Query failed: " << qry.lastQuery();
        qDebug() << '\t' << qry.lastError();
#endif

        return false;
    }

#ifdef _DEBUG
    qDebug() << "SupplierTable::Insert -- Query made: " << qry.lastQuery();
    qDebug() << "\t" << qry.lastError();
#endif

    // Send data changed signal, refresh query
    emit dataChanged();

    return true;
}

bool SupplierTable::Update(const SupplierData &data)
{
    return false;
}

bool SupplierTable::Remove(int id)
{
    QSqlQuery qry = this->query();

    qry.prepare("DELETE FROM suppliers WHERE `id`=:id");

    qry.bindValue(":id", id);

    if(!qry.exec())
    {
#ifdef _DEBUG
        qDebug() << "SupplierTable::Remove -- Query failed: " << qry.lastQuery();
        qDebug() << '\t' << qry.lastError();
#endif
        return false;
    }

#ifdef _DEBUG
    qDebug() << "Query succeeded: " << qry.lastQuery();
#endif

    return true;
}
