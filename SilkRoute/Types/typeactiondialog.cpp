#include "typeactiondialog.h"
#include "ui_typeactiondialog.h"

#include <Database/dbutils.h>
#include <QMessageBox>

TypeActionDialog::TypeActionDialog(QWidget *parent) :
    QDialog(parent)
{
    // Call constructor delegate
    construct();

    // If text in description widget is changed, call the completeRef function
    // passing its value
    this->connect(ui->txtDescription, SIGNAL(textChanged(QString)), this, SLOT(completeRef(QString)));
}

TypeActionDialog::TypeActionDialog(QWidget *parent, const TypesTable::Data &data)
    : QDialog(parent)
{
    // Call constructor delegate
    construct();

    // Set dialog data
    this->setData(data);
    // Set dialog window title
    this->setWindowTitle("Edit Type...");

    // set reference text to read only
    ui->txtRef->setReadOnly(true);
}

TypeActionDialog::~TypeActionDialog()
{
    // De-allocate UI from heap memory
    delete ui;
}

void TypeActionDialog::construct()
{
    // Create UI
    ui = new Ui::TypeActionDialog;

    // Initialize UI
    ui->setupUi(this);

    // Set the text box validation regex
    ui->txtRef->setValidator(DB::GetAlNumValidator());

    // Connect the ok button to the okBtnPressed method
    this->connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(okBtnClicked()));
}

TypesTable::Data TypeActionDialog::data() const
{
    // Initialize data container
    TypesTable::Data data;

    // Get description of the type from text box
    data.description = ui->txtDescription->text();
    // Get reference of the type from text box
    data.ref = ui->txtRef->text();

    // Return data container to caller
    return data;
}

void TypeActionDialog::setData(const TypesTable::Data &data)
{
    // Set text boxes to the given values
    ui->txtDescription->setText(data.description);
    ui->txtRef->setText(data.ref);
}

void TypeActionDialog::completeRef(const QString &val)
{
    // Grab by value
    QString desc = val;
    // Make lower case and trim whitespace
    desc = desc.toLower().trimmed();
    // Truncate all but 3 items
    desc.truncate(3);

    // set reference text box to generated text value
    ui->txtRef->setText(desc);
}

void TypeActionDialog::okBtnClicked()
{
    // Check if the text has values inside of it
    if(!ui->txtDescription->text().isEmpty())
    {
        // Send accept message to listener
        this->accept();
    }
    else
    {
        // Warn the user of invalid data
        QMessageBox::warning(this, "Invalid data entered.",
                             "Type description must be entered.",
                             QMessageBox::Ok);

        // Send rejection message to listener
        this->reject();
    }
}
