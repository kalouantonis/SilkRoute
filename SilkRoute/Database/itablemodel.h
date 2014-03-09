#ifndef ITABLEMODEL_H
#define ITABLEMODEL_H

#include <QSqlTableModel>
#include <QSqlError>
#include <SilkRoute/Database/imodel.h>

namespace DB
{

/// Represents a model using a table from a database
class ITableModel: public QSqlTableModel, public IModel
{
    Q_OBJECT

public:
    /// Class describing a database table
    explicit ITableModel(QObject* parent = 0);
    /// Empty destructor, implemented by inheritor
    virtual ~ITableModel() {}

    /// Select all items from table
    virtual void SelectAll() override;

    /// Search for item using the given term
    virtual void Search(const QString& term) = 0;
    /// Remove item from database using the given ID
    /// Returns false if query failed
    virtual bool Remove(int id) override;

    /// Get last database query error
    inline virtual const QString GetLastError() const final
    {
        return this->lastError().text();
    }

protected:
    /// Get name of database table used by this class
    virtual const QString& tableName() const = 0;

signals:
    /// Signal sent when any data is changed in class
    void dataChanged();

private slots:
    /// Reloads all table data
    inline virtual void updateAllData() final { this->SelectAll(); }

private:
    /// Used for logging
    const static QString TAG;
};

}

#endif // ITABLEMODEL_H
