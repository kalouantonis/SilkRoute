#ifndef SUPPLIERACTIONDIALOG_H
#define SUPPLIERACTIONDIALOG_H

#include <QDialog>

namespace Ui {
class SupplierActionDialog;
}

class SupplierActionDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SupplierActionDialog(QWidget *parent = 0);
    ~SupplierActionDialog();

    // Used for transferring data to and from
    // supplier widget
    typedef struct SupplierData
    {
           int id;
           QString name;
           float profit;
           float expenditure;
           int last_transaction;
    } SupplierData;
    
private:
    Ui::SupplierActionDialog *ui;
};

#endif // SUPPLIERACTIONDIALOG_H
