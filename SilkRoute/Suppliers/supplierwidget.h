#ifndef SUPPLIERWIDGET_H
#define SUPPLIERWIDGET_H

#include <SilkRoute/Base/mdiwidget.h>

// For table actions
#include <QModelIndex>

// My includes
#include <SilkRoute/Suppliers/supplieractiondialog.h>
#include <SilkRoute/Suppliers/suppliertable.h>

const QString SupplierObjectName = "SupplierWidget";

class SupplierWidget: public Base::MDIWidget
{
    Q_OBJECT
    
public:
    /// Constructor, sets parent object
    explicit SupplierWidget(QWidget *parent = 0);
    /// Destructor
    ~SupplierWidget();

    /// Get widget object name. Used in mainwindow
    static const QString& objectName() { return SupplierObjectName; }

public slots:
    /// add new supplier
    virtual void add() final;

private slots:
    /// Called on double click event, allows editing of row
    virtual void m_editAction(const QModelIndex& index) final;

private:
    /// Used for logging
    const static QString TAG;
};

#endif // SUPPLIERWIDGET_H
