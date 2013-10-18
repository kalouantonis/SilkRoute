#include "supplierwidget.h"
//#include "ui_supplierwidget.h"
#include "ui_mdiwidget.h"

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

#include <QCloseEvent>

SupplierWidget::SupplierWidget(QWidget *parent) :
    Base::MDIWidget(parent, new SupplierTable(NULL))
{

    // Resize transaction header so as to look nice
    ui->tableView->setColumnWidth(SupplierTable::LAST_TRANSACTION, ui->tableView->columnWidth(SupplierTable::LAST_TRANSACTION) + 10);

    this->setWindowTitle(tr("Suppliers"));

    // Make connections ==============================================================

    // Connect external actions
    //this->connect(this, SIGNAL(addSupplierAction()), this, SLOT(m_manipSupplier()));
}

void SupplierWidget::m_manipSupplier()
{
    SupplierActionDialog diag;

    if(diag.exec() == SupplierActionDialog::Accepted)
        qDebug() << "Dialog accepted";
}

void SupplierWidget::m_editAction(const QModelIndex &index)
{
    QMessageBox::information(this, "Not implemented",
                             "The edit functionality is yet to be implemented\nDo you want to edit row " +
                             QString::number(index.row() + 1) + "?", QMessageBox::Ok);
}

SupplierWidget::~SupplierWidget()
{
}
