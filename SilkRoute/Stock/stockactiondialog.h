#ifndef STOCKACTIONDIALOG_H
#define STOCKACTIONDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QDataWidgetMapper>

#include <SilkRoute/Suppliers/suppliertable.h>
#include <SilkRoute/Types/typestable.h>
#include "stocktable.h"

namespace Ui {
class StockActionDialog;
}

/// Dialog for adding and editing stock items
class StockActionDialog : public QDialog
{
    Q_OBJECT

public:
    /// Constructor, setting parent object and required models
    explicit StockActionDialog(QWidget *parent,
                               SupplierTable* supplierModel, TypesTable* typesModel);

    /// Constructor, setting parent object, required models and
    /// data to fill dialog with
    explicit StockActionDialog(QWidget *parent,
                               SupplierTable* supplierModel, TypesTable* typesModel,
                               const StockTable::Data& data);
    /// Destructor
    ~StockActionDialog();

    /// Get dialog data
    StockTable::Data data() const;

    /// Set the dialog data.
    void setData(const StockTable::Data& data, SupplierTable* supplierModel,
                TypesTable* typeModel);

private slots:
    /// Use index so as to get ID from model
    /// Called when supplier is changed, regenerates REF
    void genSupRef(int index);
    /// Called when type is changed, regenerates REF
    void genTypeRef(const QString& val);
    /// Called when foreign price or exchange rate fields are changed
    /// reloading the local price
    void reloadPricing();


private:
    /// Constructor delegate. C++ is limited in the way in which one constructor
    /// can not call another. This is called by both constructors to initialize
    /// this object
    void construct(SupplierTable* supplierModel, TypesTable* typesModel);

    /// Previous type reference
    QString m_previousType;

    /// Dialog user interface instance
    Ui::StockActionDialog *ui;
};

#endif // STOCKACTIONDIALOG_H
