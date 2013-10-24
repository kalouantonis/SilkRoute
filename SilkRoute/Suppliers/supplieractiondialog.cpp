#include "supplieractiondialog.h"
#include "ui_supplieractiondialog.h"

#include <Database/dbutils.h>

SupplierActionDialog::SupplierActionDialog(QWidget *parent) :
    QDialog(parent)
{
    m_construct();
}

SupplierActionDialog::SupplierActionDialog(QWidget *parent, const SupplierTable::SupplierData &data)
    : QDialog(parent)
{
    m_construct();

    ui->txtName->setText(data.name);

    // Other input fields are disabled
    ui->txtProfit->hide();
    ui->txtExpenditure->hide();
    // Hide accompanying labels
    ui->lblProfit->hide();
    ui->lblExpenditure->hide();

    this->resize(this->width(), this->height() - ui->txtProfit->height() - ui->txtExpenditure->height());
}

void SupplierActionDialog::m_construct()
{
    ui = new Ui::SupplierActionDialog;

    // Supplier with no constructor args, assuming adding
    this->setWindowTitle(tr("Add Supplier..."));

    // TODO: Move stuff so that 2 constructors can call items

    ui->setupUi(this);

    // TODO: Use validators
    ui->txtName->setValidator(DB::GetAlNumValidator(this));
    ui->txtProfit->setValidator(DB::GetNumericValidator(this));
    ui->txtExpenditure->setValidator(DB::GetNumericValidator(this));
}

SupplierTable::SupplierData SupplierActionDialog::data() const
{
    // Initialize everything as zero
    SupplierTable::SupplierData data = { 0 };

    data.name = ui->txtName->text();

    // Either enabled or in-visible
    if(ui->txtProfit->isEnabled())
        data.profit = ui->txtProfit->text().toDouble();

    if(ui->txtExpenditure->isEnabled())
        data.expenditure = ui->txtExpenditure->text().toDouble();

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
