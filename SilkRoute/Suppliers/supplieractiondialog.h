#ifndef SUPPLIERACTIONDIALOG_H
#define SUPPLIERACTIONDIALOG_H

#include <QtWidgets/QDialog>

#include <SilkRoute/Suppliers/suppliertable.h>

namespace Ui {
class SupplierActionDialog;
}


/// Dialog for adding and editing suppliers
class SupplierActionDialog : public QDialog
{
    Q_OBJECT
    
public:
    /// Constructor, setting parent object
    explicit SupplierActionDialog(QWidget *parent = 0);
    /// Constructor, setting parent object and data to fill dialog with
    explicit SupplierActionDialog(QWidget *parent, const SupplierTable::Data& data);
    /// Destructor
    ~SupplierActionDialog();


    /// Return data contained in text fields
    SupplierTable::Data data() const;

    /// Sets data in text field
    void setData(const SupplierTable::Data& data);

private slots:
    /// Called when dialog OK button is clicked
    void okBtnPressed();
    
private:
    /// Common function for constructors to call
    void construct();

    /// Dialog user interface instance
    Ui::SupplierActionDialog *ui;
};

#endif // SUPPLIERACTIONDIALOG_H
