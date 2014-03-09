#include "stockwidget.h"
#include "ui_mdiwidget.h"
#include "stocktable.h"
#include "stockactiondialog.h"

#include <SilkRoute/Base/currencyformatdelegate.h>
#include <SilkRoute/Utils/Logger.h>

#include <QSqlTableModel>
#include <QMessageBox>

const QString StockWidget::TAG = "StockWidget";

StockWidget::StockWidget(QWidget *parent) :
    Base::MDIWidget(parent, new StockTable(nullptr))
{
    // Set object name for easier recognition by parent classes
    this->setObjectName(StockObjectName);

    // Set visible window title
    this->setWindowTitle(tr("Stock"));

    // Create new window icon
    QIcon winIcon;
    // Add icon file
    winIcon.addFile(QString::fromUtf8(":stock/Resources/images/stock-view.png"), QSize(), QIcon::Normal, QIcon::On);
    // Set the icon to the window
    this->setWindowIcon(winIcon);

    // Hide ID column
    ui->tableView->hideColumn(StockTable::ID);
    // Resize all column to fit data that is contained within them
    ui->tableView->resizeColumnsToContents();

    // Set delegate for local price column
    // displaying data as formatted, localized currency
    ui->tableView->setItemDelegateForColumn(StockTable::LOCAL_PRICE,
                            new CurrencyFormatDelegate(ui->tableView));

    // Initialize and allocate supplier table model
    m_supplierTable = new SupplierTable(this);
    // Initialize and allocate type table model
    m_typesTable = new TypesTable(this);
}

StockWidget::~StockWidget()
{
    // Empty destructor
}

void StockWidget::add()
{
    // Log adding event to console
    debug(TAG, "Adding...");

    // Create new dialog, sending tables to it as references
    StockActionDialog diag(this, m_supplierTable, m_typesTable);

    // Execute dialog and check if it ok button was clicked
    if(diag.exec() == StockActionDialog::Accepted)
    {
        // Convert table model base class to stock table
        StockTable* table = static_cast<StockTable*>(m_tableModel);
        // Check if insertion of data failed
        if(!table->Insert(diag.data()))
        {
            // log to console
            error(TAG, "Insertion of a new record failed");

            // Notify the user of the failure
            QMessageBox::critical(this, "Insertion of record failed",
                          "Please consult the user manual "
                          "if this problem persists",
                           QMessageBox::Ok);
        }
    }
}

void StockWidget::m_editAction(const QModelIndex &index)
{
    // Log debugging event to console
    debug(TAG, "Editing record: "  + QString::number(index.row() + 1));

    // Initialize data container
    StockTable::Data data;

    // Get selected row for editing
    int usedRow = index.row();

    // Convert base class to StockTable type
    StockTable* stockTable = static_cast<StockTable*>(m_tableModel);
    // Get the model ID of the select row
    int id = stockTable->data(stockTable->index(usedRow, (int)StockTable::ID)).toInt();

    // Get data for selected row
    data = stockTable->Select(id);

    // Check validity of data
    if(data.id == -1)
    {
        // Query failed, exit function
        return;
    }

    // Create edit dialog, send selected data through
    StockActionDialog diag(this, m_supplierTable, m_typesTable, data);

    // If dialog was accepted
    if(diag.exec() == StockActionDialog::Accepted)
    {
        // Set data to dialog data
        data = diag.data();
        // Set the ID to the previously selected id
        data.id = id;

        // Update stock table with dialog data and check query success
        if(!stockTable->Update(data))
        {
            // Log issue to console
            error(TAG, "Failed to update records");

            // Notify user of the failure
            QMessageBox::critical(this, "Could not update record",
                            "Could not delete record. If this issue persists "
                            "refer to the user manual.",
                            QMessageBox::Ok);
        }
    }
}

