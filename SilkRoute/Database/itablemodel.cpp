#include "itablemodel.h"

#include <QSqlError>

namespace DB
{

ITableModel::ITableModel(QObject* parent)
    : QSqlQueryModel(parent)
{
    this->connect(this, SIGNAL(dataChanged()), this, SLOT(updateAllData()));
}

const QString ITableModel::GetLastError()
{
    return this->lastError().text();

    this->reset();
}

}
