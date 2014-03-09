#include "supplieractiondialog.h"
#include "ui_supplieractiondialog.h"

#include <Database/dbutils.h>
#include <QMessageBox>

SupplierActionDialog::SupplierActionDialog(QWidget *parent) :
    QDialog(parent)
{
    // Call constructor delegate. This is needed as one constructor can not call
    // another in C++
    construct();
    // set dialog window title
    this->setWindowTitle(tr("Add Supplier..."));
}

SupplierActionDialog::SupplierActionDialog(QWidget *parent, const SupplierTable::Data &data)
    : QDialog(parent)
{
    // Call constructor delegate
    construct();

    // Set dialog window title
    this->setWindowTitle(tr("Edit Supplier..."));

    // Set dialog data
    this->setData(data);
}

void SupplierActionDialog::construct()
{
    // Create UI
    ui = new Ui::SupplierActionDialog;

    // Initialize UI
    ui->setupUi(this);

    // Set the text box validation regex
    ui->txtName->setValidator(DB::GetAlNumValidator(this));
    // Connect the ok button to the okBtnPressed method
    this->connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(okBtnPressed()));
}

SupplierTable::Data SupplierActionDialog::data() const
{
    // Initialize data container
    SupplierTable::Data data;

    // Get name of supplier from text box
    data.name = ui->txtName->text();

    // Return data container to caller
    return data;
}

void SupplierActionDialog::setData(const SupplierTable::Data &data)
{
    // Set name text box to the given value
    ui->txtName->setText(data.name);
}

void SupplierActionDialog::okBtnPressed()
{
    // Get supplier name text
    QString nameText = ui->txtName->text();

    // Check if the text has values inside of it
    if(!nameText.isEmpty())
    {
        // Send accept message and close dialog
        this->accept();
    }
    else // No supplier name
    {
        // Warn the user of invalid data
        QMessageBox::warning(this, "Invalid data entered.",
                  "Supplier name must be entered.",
                    QMessageBox::Ok);

        // Send rejection message
        this->reject();
    }
}

SupplierActionDialog::~SupplierActionDialog()
{
    // De-allocate UI from heap memory
    delete ui;
}
