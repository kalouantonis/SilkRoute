#include "supplieractiondialog.h"
#include "ui_supplieractiondialog.h"

#include <Database/itable.h>

SupplierActionDialog::SupplierActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SupplierActionDialog)
{
    // Supplier with no constructor args, assuming adding
    this->setWindowTitle(tr("Add Supplier..."));

    // TODO: Move stuff so that 2 constructors can call items

    ui->setupUi(this);

    // TODO: Use validators
    ui->txtName->setValidator(DB::ITable::GetAlNumValidator(this));
}

SupplierTable::SupplierData SupplierActionDialog::data() const
{
    // Initialize everything as zero
    SupplierTable::SupplierData data = { 0 };

    data.name = ui->txtName->text();

    return data;
}

void SupplierActionDialog::setData(const SupplierTable::SupplierData &data)
{
    ui->txtName->setText(data.name);
}

SupplierActionDialog::~SupplierActionDialog()
{
    delete ui;
}
