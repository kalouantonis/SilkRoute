#include "mdiwidget.h"
#include "ui_mdiwidget.h"

#include <QDebug>
#include <QMessageBox>
#include <Database/dbutils.h>
#include <SilkRoute/Utils/Logger.h>
#include <SilkRoute/Base/itemreferencedexception.h>

namespace Base
{

const QString MDIWidget::TAG = "MDIWidget";

MDIWidget::MDIWidget(QWidget *parent, DB::ITableModel* tableModel) :
    QWidget(parent),        // Parent constructor
    ui(new Ui::MDIWidget)   // UI constructor
{
    // Initialize user interface
    ui->setupUi(this);

    // Set widget object name to its specified tag value
    this->setObjectName(TAG);

    // Attach sql model to table view
    attachModel(tableModel);

    // Set search validator, so as to avoid SQL Injections
    ui->txtSearch->setValidator(DB::GetAlNumValidator(this));

    // Resize all columns to fit contents
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QTableView::NoEditTriggers);

    // Make connections =================================================================
    //txtSearch
    this->connect(ui->txtSearch, SIGNAL(returnPressed()), this, SLOT(m_searchAction()));
    // Clear search, reset model
    this->connect(ui->btnClearSearch, SIGNAL(clicked()), this, SLOT(m_clearSearch()));

    // Double click action, allows editing
    this->connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(m_editAction(QModelIndex)));
}


void MDIWidget::attachModel(DB::ITableModel *model)
{
    // Set class attribute to the specified model
    m_tableModel = model;

    // Attach model to view
    ui->tableView->setModel(m_tableModel);
}

void MDIWidget::m_searchAction()
{
    // Set search term using search text box
    QString search = ui->txtSearch->text();

    // Check if search is not empty
    if(!search.isEmpty())
    {
        // Call search using the sql model
        m_tableModel->Search(search);

        // Exit function
        return;
    }

    // Search is empty, select all data
    m_tableModel->SelectAll();
}

void MDIWidget::m_clearSearch()
{
    // Clear txtSearch
    ui->txtSearch->clear();

    // Reset model
    m_tableModel->SelectAll();
}

void MDIWidget::m_editAction(const QModelIndex &)
{
    // Does nothing, supposed to be implemented by inheritor
}

MDIWidget::~MDIWidget()
{
    if(m_tableModel) // If not NULL
    {
        // De-allocate sql model from memory
        delete m_tableModel;
        // Log to console
        debug(TAG, "Deleted table model...");
    }

    // Delete UI elements
    delete ui;
    // Log to console
    debug(TAG, "Deleted UI...");
}

void MDIWidget::remove()
{
    // Get selected items
    QModelIndexList selectedItems = ui->tableView->selectionModel()->selectedRows();

    // Check if there are selected items by checking if list is empty
    if(!selectedItems.empty())
    {
        // Get return value from the created "Yes" & "No" message box
        int ret = QMessageBox::warning(this, "Delete record?",
                                       "Are you sure you want to delete this record?",
                                       QMessageBox::Yes | QMessageBox::No);

        // Check if return value corresponds to clicking the 'Yes' button
        if(ret == QMessageBox::Yes)
        {
            // Get corresponding sql id for the first selected items
            // Will only allow deletion of one item at a time
            int modelId = m_tableModel->data(selectedItems.first()).toInt();

            // Surround by try block, to catch any exceptions
            try
            {
                // Call sql model to remove the specified ID
                // Check if removal was a failure
                if(!m_tableModel->Remove(modelId))
                {
                    // Create a message box notifying the user that deletion failed
                    QMessageBox::critical(this, "Could not remove record.",
                              "There was an internal error. Please consult the FAQ",
                              QMessageBox::Ok);

                    // log to console
                    debug(TAG, "Failed to remove record. ID: " + modelId);
                }
            }
            // Item referenced exception has occured
            // We can not remove the item because it is already referenced
            catch(ItemReferencedException& e)
            {
                // Notify user
                QMessageBox::warning(this, "Could not remove record.",
                             "Record is referenced by one or more items.",
                             QMessageBox::Ok);

                // Log exception message to console
                debug(TAG, e.what());
            }
        }
    }
}

} // Namespace Base
