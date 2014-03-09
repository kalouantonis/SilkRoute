#include "stockactiondialog.h"
#include "ui_stockactiondialog.h"

#include <SilkRoute/Utils/Logger.h>
#include <SilkRoute/Database/dbutils.h>
#include <SilkRoute/Base/mathutils.h>


StockActionDialog::StockActionDialog(QWidget *parent, SupplierTable *supplierModel, TypesTable *typesModel)
    : QDialog(parent) // Parent constructor
{
    // Call constructor delegate. This is needed as one constructor can not call
    // another in C++
    construct(supplierModel, typesModel);
}

StockActionDialog::StockActionDialog(QWidget *parent, SupplierTable *supplierModel, TypesTable *typesModel, const StockTable::Data &data)
    : QDialog(parent) // Parent constructor
{
    // Call constructor delegate
    construct(supplierModel, typesModel);
    // Set dialog data
    setData(data, supplierModel, typesModel);

    // Set dialog window title
    this->setWindowTitle("Edit Stock...");
}

void StockActionDialog::construct(SupplierTable *supplierModel, TypesTable *typesModel)
{
    // Create UI
    ui = new Ui::StockActionDialog;
    // Initialize UI
    ui->setupUi(this);

    // Connect combo box events to methods. ////////////////////////////////////

    // Call genSupRef when index of supplier combo box is changed
    this->connect(ui->comboSupplier, SIGNAL(currentIndexChanged(int)),
                  this, SLOT(genSupRef(int)));
    // Call genTypeRef when text inside type combo box is changed
    this->connect(ui->comboType, SIGNAL(currentTextChanged(QString)),
                  this, SLOT(genTypeRef(QString)));
    // Call reloadPricing when foreign price is changed
    this->connect(ui->txtForeignPrice, SIGNAL(textChanged(QString)),
                  this, SLOT(reloadPricing()));
    // Call reloadPricing when exchange_rate is changed
    this->connect(ui->txtExchangeRate, SIGNAL(textChanged(QString)),
                  this, SLOT(reloadPricing()));

   /////////////////////////////////////////////////////////////////////////////


    // only select items that are not marked as deleted
    supplierModel->setFilter("deleted=0");
    // Select all model data
    supplierModel->select();
    // Sort by supplier name in alphabetical order
    supplierModel->sort(SupplierTable::NAME, Qt::AscendingOrder);
    // Set combo box model to load data from
    ui->comboSupplier->setModel(supplierModel);
    // Display data from name column
    ui->comboSupplier->setModelColumn(SupplierTable::NAME);

    // only select items that are not marked as deleted
    typesModel->setFilter("deleted=0");
    // Select all model data
    typesModel->select();
    // Sort by type reference in alphabetical order
    typesModel->sort(TypesTable::REF, Qt::AscendingOrder);
    // Set combo box model to load data from
    ui->comboType->setModel(typesModel);
    // Display data from reference column
    ui->comboType->setModelColumn(TypesTable::REF);

    // Reload supplier and type generated refs
    genTypeRef(ui->comboType->currentText());
    genSupRef(ui->comboType->currentIndex());
    // Reload pricing using set price
    reloadPricing();

    // Get validator for only numeric characters
    QValidator* validator = DB::GetNumericValidator(this);

    // Set validators for currency input
    ui->txtForeignPrice->setValidator(validator);
    ui->txtExchangeRate->setValidator(validator);
}

StockActionDialog::~StockActionDialog()
{
    // De-allocate UI from heap memory
    delete ui;
}

StockTable::Data StockActionDialog::data() const
{
    // Create stock data container and initialize all values to 0 or NULL
    StockTable::Data data = { 0 };

    // Get supplier model from supplier combo box
    QAbstractItemModel* supplierModel = ui->comboSupplier->model();
    // Grab supplier ID from model
    int supplierId = supplierModel->index(ui->comboSupplier->currentIndex(),
                                      SupplierTable::ID).data().toInt();

    // Set supplier id in container from given model id
    data.supplier_id = supplierId;

    // Get type model from type combo box
    QAbstractItemModel* typeModel = ui->comboType->model();
    // Grab type ID from model and set it in to data container
    data.type_id = typeModel->index(ui->comboType->currentIndex(), TypesTable::ID)
            .data().toInt();

    // Generate reference using type reference, foreign price and the supplier id
    data.ref = ui->comboType->currentText() + ui->txtForeignPrice->text().remove('.') +
            '-' + QString::number(supplierId);

    // Get foreign price from text box as double
    data.foreign_price = ui->txtForeignPrice->text().toDouble();
    // Get exchange rate from text box as float
    data.exchange_rate = ui->txtExchangeRate->text().toFloat();
    // Calculate local price using exchange rates, round result to 2dp
    data.local_price = round2dp(data.foreign_price * data.exchange_rate);
    // round foreign price to 2dp
    data.foreign_price = round2dp(data.foreign_price);

    // return data container to caller
    return data;
}

void StockActionDialog::setData(const StockTable::Data &data, SupplierTable *supplierModel, TypesTable *typeModel)
{
    // Set supplier combo box index to the view index given by the model index
    ui->comboSupplier->setCurrentIndex(DB::GetViewIndex(data.supplier_id, supplierModel));
    // Set type combo box index to the view index given by the model index
    ui->comboType->setCurrentIndex(DB::GetViewIndex(data.type_id, typeModel));
    // Set foreign price to data provided as method argument
    ui->txtForeignPrice->setText(QString::number(data.foreign_price));
    // Set exchange rate to data provided as method argument
    ui->txtExchangeRate->setText(QString::number(data.exchange_rate));
    // Set local price to data provided as method argument
    ui->txtLocalPrice->setText(QString::number(data.local_price));
    // Set the generated reference to data provided as method argument
    ui->txtGenRef->setText(data.ref);
}

void StockActionDialog::genSupRef(int index)
{
    // Grab supplier ID from model using corresponding current selected index
    int id = ui->comboSupplier->model()->index(index, SupplierTable::ID).
            data().toInt();

    // Get current generated reference text
    QString boxText = ui->txtGenRef->text();

    // check if text contains the - symbol
    if(!boxText.contains('-'))
    {
        // insert text on to end of generated ref text
        boxText += '-' + QString::number(id);
    }
    else
    {
        // Remove last item and replace with new item
        boxText = boxText.replace(boxText.indexOf('-') + 1, 1, QString::number(id));
    }

    // set generated ref text
    ui->txtGenRef->setText(boxText);
}

void StockActionDialog::genTypeRef(const QString &val)
{
    // Get generated reference text
    QString boxText = ui->txtGenRef->text();
    // Remove previous type reference
    boxText.remove(0, m_previousType.length() - 1);
    // Prepend new value in to generated ref
    boxText.prepend(val);

    // set generated text box value
    ui->txtGenRef->setText(boxText);

    // store current type ref
    m_previousType = boxText;
}

void StockActionDialog::reloadPricing()
{
    // get foreign price from foreign price text box
    double foreign_price = ui->txtForeignPrice->text().toDouble();

    // Set local price text box using foreign price and exchange rate
    ui->txtLocalPrice->setText(QString::number(
                   // round resultant value to 2dp
                   round2dp(foreign_price * ui->txtExchangeRate->text().toDouble())
    ));

    // get generated reference text
    QString boxText = ui->txtGenRef->text();
    // insert the value at the end of the type ref
    boxText.insert(ui->comboType->currentText().length(),
                   QString::number(round2dp(foreign_price)));
    // Set generated reference text box value
    ui->txtGenRef->setText(boxText);
}
