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
    ui(new Ui::SupplierWidget),
    m_supplierModel()
{
    ui->setupUi(this);

    m_supplierModel.setQuery("SELECT * FROM suppliers");

    // Set header data
    m_supplierModel.setHeaderData(ID, Qt::Horizontal, QObject::tr("Ref"));
    m_supplierModel.setHeaderData(NAME, Qt::Horizontal, QObject::tr("Name"));
    m_supplierModel.setHeaderData(PROFIT, Qt::Horizontal, QObject::tr("Profit"));
    m_supplierModel.setHeaderData(EXPENDITURE, Qt::Horizontal, QObject::tr("Expenditure"));
    // Allow clicking to open transaction window
    m_supplierModel.setHeaderData(LAST_TRANSACTION, Qt::Horizontal, QObject::tr("Last Transaction"));

    // Set model delegate
    ui->tableView->setModel(&m_supplierModel);

    // Resize transaction header so as to look nice
    ui->tableView->setColumnWidth(LAST_TRANSACTION, ui->tableView->columnWidth(LAST_TRANSACTION) + 10);
}

void SupplierWidget::searchAction()
{
#ifdef _DEBUG
    qDebug() << "Searching Suppliers...";
#endif

    // Temp variable to check weather dialog was accepted
    bool accepted;
    QString search = QInputDialog::getText(this, tr("Search Suppliers"), tr("Condition"),
                                           QLineEdit::Normal, QString(), &accepted);

    if(accepted)
    {
        QString query("SELECT * FROM suppliers");

        if(!search.isEmpty())
        {
            // Sanitize input
            search = DB::ITable::SanitizeQuery(search);

            query += " WHERE id LIKE \"%" + search + "%\" OR name LIKE \"%" + search + "%\"";
        }


        // Change model query
        m_supplierModel.setQuery(query);

#ifdef _DEBUG
        qDebug() << "Query made: " + query +
                    "\n\tFound " + QString::number(m_supplierModel.rowCount()) + " rows" +
                    "\n\tErrors: " << m_supplierModel.lastError();
#endif
    }
}

SupplierWidget::~SupplierWidget()
{
    delete ui;
}
