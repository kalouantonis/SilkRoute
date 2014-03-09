#ifndef INITUTILS_H
#define INITUTILS_H

#include <QSqlQuery>
#include <QSqlError>
#include <QRegExpValidator>
#include <QSqlQueryModel>

#include <QDebug>

namespace DB
{

/// Create all needed tables from given schema file
bool CreateAllTables(const QString& filename);

/// Returns alphanumberic regex expression for use as a validator
QRegExpValidator* GetAlNumValidator(QObject* parent = 0);
/// Returns numeric regex expression
QRegExpValidator* GetNumericValidator(QObject* parent = 0);
/// Returns numeric regex expression that does not allow negative values
QRegExpValidator* GetNonNegativeNumericValidator(QObject* parent = 0);

/// Optimized query preperation
QSqlQuery& PrepareQuery(const QString& query);

/// Get Qt view index from a given model index
int GetViewIndex(int modelIndex, const QSqlQueryModel* model);

}

#endif // INITUTILS_H
