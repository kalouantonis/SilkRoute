#ifndef INITUTILS_H
#define INITUTILS_H

#include <QSqlQuery>
#include <QSqlError>
#include <QRegExpValidator>

#include <QDebug>

namespace DB
{

// Create all needed tables
bool CreateAllTables(const QString& filename);

// Returns alphanumberic regex expression for use as a validator
QRegExpValidator* GetAlNumValidator(QObject* parent = 0);
QRegExpValidator* GetNumericValidator(QObject* parent = 0);

}

#endif // INITUTILS_H
