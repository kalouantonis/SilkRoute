#include "supplieractiondialog.h"
#include "ui_supplieractiondialog.h"

SupplierActionDialog::SupplierActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SupplierActionDialog)
{
    ui->setupUi(this);
}

SupplierActionDialog::~SupplierActionDialog()
{
    delete ui;
}
