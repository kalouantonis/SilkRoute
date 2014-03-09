#include "supplierwidget.h"
#include "ui_mdiwidget.h"

// For error messages
#include <QMessageBox>

#include <SilkRoute/Utils/Logger.h>
#include <SilkRoute/Base/currencyformatdelegate.h>


const QString SupplierWidget::TAG = "SupplierWidget";

SupplierWidget::SupplierWidget(QWidget *parent) :
    Base::MDIWidget(parent, new SupplierTable(NULL))
{
    // Better recognition from parents
    this->setObjectName(SupplierObjectName);

    // Hide vertical header as it will conflict with ID's
    ui->tableView->verticalHeader()->hide();

    // Set delegate for profit column
    // displaying data as formatted, localized currency
    ui->tableView->setItemDelegateForColumn(SupplierTable::PROFIT,
                                    new CurrencyFormatDelegate(ui->tableView));

    // Set window title of widget.
    this->setWindowTitle(tr("Suppliers"));

    // Set icon for window
    QIcon winIcon;
    // Add icon file
    winIcon.addFile(QString::fromUtf8(":suppliers/Resources/images/supplier-view.png"), QSize(), QIcon::Normal, QIcon::On);
    // Set the icon to the window
    this->setWindowIcon(winIcon);
}

void SupplierWidget::add()
{
    // Log adding event to console
    debug(TAG, "Adding...");

    // Create new dialog, setting the parent as this
    SupplierActionDialog diag(this);

    // Execute dialog and check if ok button was pressed
    if(diag.exec() == SupplierActionDialog::Accepted)
    {
        // Convert to SupplierTable, I know its safe, because I declared
        // the type in the constructor
        SupplierTable* table = static_cast<SupplierTable*>(m_tableModel);
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

void SupplierWidget::m_editAction(const QModelIndex &index)
{
    // Log debugging event to console
    debug(TAG, "Editing record: "  + QString::number(index.row() + 1));

    // Get data from table index
    SupplierTable::Data data = { 0 };

    // Get selected row for editing
    int usedRow = index.row();

    // Convert base class to StockTable type
    SupplierTable* model = static_cast<SupplierTable*>(m_tableModel);

    // Fill previous data
    data.name = model->data(model->index(usedRow, (int)SupplierTable::NAME)).toString();
    // Grab ID from table
    data.id = model->data(model->index(usedRow, (int)SupplierTable::ID)).toInt();

    // Create edit dialog, send selected data through
    SupplierActionDialog diag(this, data);

    // If dialog was accepted
    if(diag.exec() == SupplierActionDialog::Accepted)
    {
        // Modify name with dialog name
        data.name = diag.data().name;

        if(!model->Update(data))
            qDebug() << "Update statement failed: SupplierWidget::m_editAction()";
    }
}

SupplierWidget::~SupplierWidget()
{
    // Empty destructor
}
