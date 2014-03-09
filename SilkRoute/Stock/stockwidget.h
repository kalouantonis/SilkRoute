#ifndef STOCKWIDGET_H
#define STOCKWIDGET_H

#include <SilkRoute/Base/mdiwidget.h>
#include <SilkRoute/Suppliers/suppliertable.h>
#include <SilkRoute/Types/typestable.h>

const QString StockObjectName = "StockWidget";

class StockWidget : public Base::MDIWidget
{
    Q_OBJECT
    
public:
    /// Constructor, sets parent object
    explicit StockWidget(QWidget *parent = nullptr);
    /// Destructor
    ~StockWidget();

    /// Returns object identifier
    static const QString& objectName() { return StockObjectName; }

public slots:
    /// Called when new stock item is requested
    virtual void add() final;

private slots:
    /// Called when edit is requested
    virtual void m_editAction(const QModelIndex& index) override;

private:
    /// Supplier table for use in dialog
    SupplierTable* m_supplierTable;
    /// Type table for use in dialog
    TypesTable* m_typesTable;

    /// Used for logging
    const static QString TAG;
};

#endif // STOCKWIDGET_H
