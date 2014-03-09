#ifndef IMODEL_H
#define IMODEL_H

#include <QString>

namespace DB
{

/// Purely virtual class. Used for polymorphic calls
class IModel
{
public:
    /// Destructor. Set as empty, inheritor defines behaviour
    virtual ~IModel() {}

    /// Select all data from database
    virtual void SelectAll() = 0;
    /// Search data in database using a given term
    virtual void Search(const QString& term) = 0;
    /// Remove an item from database using the given id
    /// Returns true if removal was a success, or false if failed
    virtual bool Remove(int id) = 0;

    /// Get the last error from the database query
    virtual const QString GetLastError() const = 0;

protected:
    /// The database table name
    inline virtual const QString& tableName() const = 0;

protected slots:
    /// Called when data is changed so as to refresh all table data
    virtual void updateAllData() = 0;

};

}

#endif // IMODEL_H
