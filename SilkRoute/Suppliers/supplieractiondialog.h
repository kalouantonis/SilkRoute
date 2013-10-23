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
    /*
    typedef struct SupplierData
    {
           int id;
           QString name;
           //float profit;
           //float expenditure;
           //int last_transaction;
    } SupplierData;*/

    typedef QString SupplierData;

    // Return data contained in text field
    SupplierData data() const;

    // Sets data in text field
    void setData(const SupplierData& data);

    
private:
    Ui::SupplierActionDialog *ui;
};

#endif // SUPPLIERACTIONDIALOG_H
