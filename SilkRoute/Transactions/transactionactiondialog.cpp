#include "transactionactiondialog.h"
#include "ui_transactionactiondialog.h"

#include <SilkRoute/Transactions/plusminuspushwidget.h>
#include <SilkRoute/Database/dbutils.h>
#include <SilkRoute/Base/mathutils.h>

#include <QSqlRelation>
#include <QSqlRelationalDelegate>
#include <QWidget>
#include <QSqlIndex>
#include <QLineEdit>

TransactionActionDialog::TransactionActionDialog(QWidget *parent, StockTable* stockTable)
    : QDialog(parent)
    , m_stockTable(stockTable)
{
    // Call constructor delegate
    construct();
}

TransactionActionDialog::TransactionActionDialog(QWidget *parent, StockTable *stockTable, const QVector<TransactionTable::Data> &data)
    : QDialog(parent)
    , m_stockTable(stockTable)
{
    // Call constructor delegate
    construct();
    // Set dialog data
    setData(data);

    // Set dialog window title
    this->setWindowTitle("Edit Transactions...");
}

void TransactionActionDialog::construct()
{
    // Create UI
    ui = new Ui::TransactionActionDialog;

    // Initialize UI
    ui->setupUi(this);

    // Set header labels
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "Stock Item"
                                                << "Amount" << "Positive/Negative" << "No. Items"
                                               << "Deleted");
    // Hide ID column
    ui->tableWidget->hideColumn(ID);
    // Hide deleted column
    ui->tableWidget->hideColumn(DELETED);

    // Reize positive/negative column to fit data
    ui->tableWidget->resizeColumnToContents(POS_NEG);

    // Set date widget to current date
    ui->date->setDate(QDate::currentDate());

    // Connect buttons to slots
    this->connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(m_addTrans()));
    this->connect(ui->btnRemove, SIGNAL(clicked()), this, SLOT(m_removeTrans()));
}


TransactionActionDialog::~TransactionActionDialog()
{
    // De-allocate UI from heap memory
    delete ui;
}

QVector<TransactionTable::Data> TransactionActionDialog::data() const
{
    // List containing transaction table data containers
    QVector<TransactionTable::Data> dataList;

    // Temporary variables to avoid stack re-allocation
    QComboBox* comboBox;
    PlusMinusPushWidget* plusMinusWidget;
    TransactionTable::Data rowData;

    // Iterate through each row
    for(int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        // Get amount from text box, convert to double and round to 2dp
        rowData.amount = round2dp(static_cast<QLineEdit*>(ui->tableWidget->cellWidget(i, AMOUNT))
                ->text().toDouble());


        // get date from date widget
        rowData.trans_date = ui->date->date();

        // get stock item combo box
        comboBox = static_cast<QComboBox*>(ui->tableWidget->cellWidget(i, STOCK_ITEM));
        // get model id from selected index
        rowData.stock_id = comboBox->model()->index(
                    comboBox->currentIndex(),
                    StockTable::ID
         ).data().toInt();

        // Get the number sold, ignore decimal points
        rowData.noSold = std::trunc(static_cast<QLineEdit*>(ui->tableWidget->cellWidget(i, NO_SOLD))
                ->text().toDouble());

        // get plus minus widget
        plusMinusWidget = static_cast<PlusMinusPushWidget*>(
                    ui->tableWidget->cellWidget(i, POS_NEG)
        );
        // is button clicked
        if(plusMinusWidget->isClicked())
            // Inverse value of number sold
            rowData.noSold *= -1;

        // Set deleted according to text box value in DELETED column
        rowData.deleted = static_cast<QLineEdit*>(ui->tableWidget->cellWidget(i, DELETED))
                ->text().toInt();

        // Set id according to text box value in ID column
        rowData.id = static_cast<QLineEdit*>(ui->tableWidget->cellWidget(i, ID))
                ->text().toInt();

        // Check amounts and no sold
        if(rowData.amount > 0 && rowData.noSold > 0)
        {
            // Throw exception to be caught by caller
            throw InvalidAmountException("Check row " +
                                 QString::number(i+1) +
                                ". Positive amounts with positive stock "
                                         "amounts are not allowed.");
        }
        else if(rowData.amount < 0 && rowData.noSold < 0)
        {
            // Throw exception to be caught by caller
            throw InvalidAmountException("Check row " +
                                         QString::number(i+1) +
                                         ". Positive amounts with negative stock "
                                         "amounts are not allowed.");
        }

        // Add row data on to list of data containers
        dataList.push_back(rowData);
    }

    return dataList;
}

void TransactionActionDialog::setData(const QVector<TransactionTable::Data> &data)
{
    for(const TransactionTable::Data& item: data)
    {
        // Add new transaction
        int currRow = ui->tableWidget->rowCount();

        // Insert row after current row
        ui->tableWidget->insertRow(currRow);

        // Create new plus minus widget
        PlusMinusPushWidget* plusMinusWidget = new PlusMinusPushWidget(
                    ui->tableWidget);

        // Create temporary variable to hold the item amount.
        // This is due to the const restrictions, we can not modify the value
        // directly
        int tempNoStock = item.noSold;

        // Check if value is negative
        if(tempNoStock < 0)
        {
            // Click the button so that its set to -
            plusMinusWidget->click();
            // Make value positive
            tempNoStock *= -1;
        }


        // Set the plus minus widget to the table
        ui->tableWidget->setCellWidget(currRow, POS_NEG, plusMinusWidget);

        // Create combo box that links to stock table model
        // and add to row and column
        QComboBox* comboBox = new QComboBox(ui->tableWidget);
        comboBox->setModel(m_stockTable);
        // show the reference column
        comboBox->setModelColumn(StockTable::REF);

        // get view index from model
        int stock_index = DB::GetViewIndex(item.stock_id,
                         static_cast<QSqlQueryModel*>(m_stockTable));

        // Set index of row to view index we found earlier
        comboBox->setCurrentIndex(stock_index);
        // Set widget to table
        ui->tableWidget->setCellWidget(currRow, STOCK_ITEM, comboBox);

        // create new line edit containing amount data
        QLineEdit* lineEdit = new QLineEdit(QString::number(item.amount, 'd', 2), ui->tableWidget);
        // set numeric values only regex
        lineEdit->setValidator(DB::GetNumericValidator(lineEdit));

        // set line edit in to amount column
        ui->tableWidget->setCellWidget(currRow, AMOUNT,
                   lineEdit);

        // create new line edit containing number of stock data
        lineEdit = new QLineEdit(QString::number(tempNoStock), ui->tableWidget);
        // set validator as non negative regex
        lineEdit->setValidator(DB::GetNonNegativeNumericValidator(lineEdit));

        // set the line edit widget in to the no sold column
        ui->tableWidget->setCellWidget(currRow, NO_SOLD, lineEdit);

        // create line edit, add id number and insert in to id column
        ui->tableWidget->setCellWidget(currRow, ID,
                   new QLineEdit(QString::number(item.id), ui->tableWidget));

        // create line edit, add deleted mark and insert in to deleted column
        ui->tableWidget->setCellWidget(currRow, DELETED,
                   new QLineEdit(QString::number(item.deleted, 'd', 2), ui->tableWidget));
    }
}

int TransactionActionDialog::m_addTrans()
{
    // Get last row index
    int currRow = ui->tableWidget->rowCount();

    // Insert row after current row
    ui->tableWidget->insertRow(currRow);

    //ui->tableWidget->item(currRow, ID)->setData(Qt::DisplayRole, QVariant(-1));

    auto* plusMinusWidget = new PlusMinusPushWidget(ui->tableWidget);
    // Set to minus by default
    plusMinusWidget->click();
    // set widget in to Positive/Negative row
    ui->tableWidget->setCellWidget(currRow, POS_NEG, plusMinusWidget);

    // Create combo box that links to stock table model
    // and add to row and column
    QComboBox* comboBox = new QComboBox(ui->tableWidget);
    comboBox->setModel(m_stockTable);
    comboBox->setModelColumn(StockTable::REF);
    // add combo box in to stock item column
    ui->tableWidget->setCellWidget(currRow, STOCK_ITEM, comboBox);

    // create line edit, default to 0 value
    QLineEdit* lineEdit = new QLineEdit(QString::number(0), ui->tableWidget);
    // set numeric regex as validator
    lineEdit->setValidator(DB::GetNumericValidator(lineEdit));

    // set line edit in to amount column
    ui->tableWidget->setCellWidget(currRow, AMOUNT,
               lineEdit);

    // create new line edit containing number of stock data
    lineEdit = new QLineEdit(QString::number(0), ui->tableWidget);
    // set validator as non negative regex
    lineEdit->setValidator(DB::GetNonNegativeNumericValidator(lineEdit));
    // set the line edit widget in to the no sold column
    ui->tableWidget->setCellWidget(currRow, NO_SOLD,
               lineEdit);

    // create line edit, add id number and insert in to id column
    ui->tableWidget->setCellWidget(currRow, ID,
               new QLineEdit(QString::number(-1), ui->tableWidget));

    // create line edit, add deleted mark and insert in to deleted column
    ui->tableWidget->setCellWidget(currRow, DELETED,
               new QLineEdit(QString::number(0), ui->tableWidget));

    // return new row index to caller
    return currRow;
}

void TransactionActionDialog::m_removeTrans()
{
    // Get selected items
    const QModelIndexList& selectedItems = ui->tableWidget->selectionModel()
            ->selectedRows();

    // Iterate over selected items
    for(const QModelIndex& index : selectedItems)
    {
        static_cast<QLineEdit*>(ui->tableWidget->cellWidget(index.row(), DELETED))
                ->setText(QString::number(1));
        // Hide selected row from user
        ui->tableWidget->hideRow(index.row());
    }
}
