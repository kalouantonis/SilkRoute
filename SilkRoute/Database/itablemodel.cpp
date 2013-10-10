#include "itablemodel.h"

#include <QSqlError>

namespace DB
{

ITableModel::ITableModel(QObject* parent)
    : QSqlQueryModel(parent)
{
}

const QString ITableModel::GetLastError()
{
    return this->lastError().text();

    this->reset();
}

}
