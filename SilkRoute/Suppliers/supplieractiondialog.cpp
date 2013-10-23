#include "supplieractiondialog.h"
#include "ui_supplieractiondialog.h"

SupplierActionDialog::SupplierActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SupplierActionDialog)
{
    ui->setupUi(this);
}

SupplierActionDialog::SupplierData SupplierActionDialog::data() const
{
    return ui->txtName->text();
}

void SupplierActionDialog::setData(const SupplierData &data)
{
    ui->txtName->setText(data);
}

SupplierActionDialog::~SupplierActionDialog()
{
    delete ui;
}
