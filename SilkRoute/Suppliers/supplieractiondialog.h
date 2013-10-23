#ifndef SUPPLIERACTIONDIALOG_H
#define SUPPLIERACTIONDIALOG_H

#include <QDialog>

#include <SilkRoute/Suppliers/suppliertable.h>

namespace Ui {
class SupplierActionDialog;
}

class SupplierActionDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SupplierActionDialog(QWidget *parent = 0);
    ~SupplierActionDialog();


    // Return data contained in text field
    SupplierTable::SupplierData data() const;

    // Sets data in text field
    void setData(const SupplierTable::SupplierData& data);

    
private:
    Ui::SupplierActionDialog *ui;
};

#endif // SUPPLIERACTIONDIALOG_H
