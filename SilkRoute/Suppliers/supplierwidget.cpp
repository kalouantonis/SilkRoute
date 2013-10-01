#include "supplierwidget.h"
#include "ui_supplierwidget.h"

#include <QDebug>

// For search func
#include <QInputDialog>

// SQL Errors
#include <QSqlError>

// For error messages
#include <QMessageBox>

// For sanitization
#include <SilkRoute/Database/itable.h>

// For exceptions
#include <stdexcept>

// STD Strings
#include <string>

SupplierWidget::SupplierWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupplierWidget)
{
    ui->setupUi(this);

    // Set up model
    m_supplierModel = new SupplierTable(this);

    // Set model delegate
    ui->tableView->setModel(m_supplierModel);

    // Resize transaction header so as to look nice
    ui->tableView->setColumnWidth(SupplierTable::LAST_TRANSACTION, ui->tableView->columnWidth(SupplierTable::LAST_TRANSACTION) + 10);

    // Set search validator, so as to avoid SQL Injections
    ui->txtSearch->setValidator(DB::ITable::GetAlNumValidator(this));

    // Make connections ==============================================================
    //txtSearch
    this->connect(ui->txtSearch, SIGNAL(returnPressed()), this, SLOT(m_searchAction()));
    // Clear search, reset model
    this->connect(ui->btnClearSearch, SIGNAL(clicked()), this, SLOT(m_clearSearch()));

    //double click action allows editing
    this->connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(m_editAction(QModelIndex)));

    // Connect external actions
    this->connect(this, SIGNAL(addSupplierAction()), this, SLOT(m_manipSupplier()));
}

void SupplierWidget::m_searchAction()
{
#ifdef _DEBUG
    qDebug() << "Searching Suppliers...";
#endif

    QString search = ui->txtSearch->text();

    QString query("SELECT * FROM suppliers");

    if(!search.isEmpty())
    {
        // Sanitize input
        //search = DB::ITable::SanitizeQuery(search);

        query += " WHERE id LIKE \"%" + search + "%\" OR name LIKE \"%" + search + "%\"";
    }


    // Change model query
    m_supplierModel->setQuery(query);

#ifdef _DEBUG
    qDebug() << "Query made: " + query +
                "\n\tFound " + QString::number(m_supplierModel->rowCount()) + " rows" +
                "\n\tErrors: " << m_supplierModel->lastError().text();
#endif
}

void SupplierWidget::m_manipSupplier()
{
    SupplierActionDialog diag;

    if(diag.exec() == SupplierActionDialog::Accepted)
        qDebug() << "Dialog accepted";

}

void SupplierWidget::m_clearSearch()
{
    // Clear search from txtSearch
    ui->txtSearch->clear();

    // Reset model
    m_supplierModel->setQuery("SELECT * FROM suppliers");
}

void SupplierWidget::m_editAction(const QModelIndex &index)
{
QMessageBox::information(this, "Not implemented",
                         "The edit functionality is yet to be implemented\nDo you want to edit row " +
                         QString::number(index.row()) + "?", QMessageBox::Ok);

}

SupplierWidget::~SupplierWidget()
{
delete ui;
}
