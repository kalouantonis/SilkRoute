#ifndef TYPESTABLE_H
#define TYPESTABLE_H

//#include <Database/itablemodel.h>
#include <SilkRoute/Database/itablemodel.h>

class TypesTable: public DB::ITableModel
{
    Q_OBJECT

public:
    TypesTable(QObject* parent = nullptr);

    typedef struct Data
    {
        int id;
        QString ref;
        QString description;
    } Data;

    enum TYPE_COLUMNS
    {
        ID,
        REF,
        DESCRIPTION,
        DELETED
    };

    virtual void Search(const QString &term) final;

    bool RefExists(const QString& ref);

    bool Insert(const Data& data);
    bool Update(const Data& data);
    virtual bool Remove(int id) override;

private:
    static const QString internalTableName;

    // Used for logging
    static const QString TAG;

    // ITableModel interface
protected:
    virtual const QString &tableName() const override { return internalTableName; }
};

#endif // TYPESTABLE_H
