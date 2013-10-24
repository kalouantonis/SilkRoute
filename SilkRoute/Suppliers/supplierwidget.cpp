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
    // Better recognition from parents
    this->setObjectName(SupplierObjectName);

    // Resize transaction header so as to look nice
    ui->tableView->setColumnWidth(SupplierTable::LAST_TRANSACTION, ui->tableView->columnWidth(SupplierTable::LAST_TRANSACTION) + 10);

    this->setWindowTitle(tr("Suppliers"));

    // Set icon for window
    QIcon winIcon;
    winIcon.addFile(QString::fromUtf8(":suppliers/Resources/images/supplier-view.png"), QSize(), QIcon::Normal, QIcon::On);
    this->setWindowIcon(winIcon);

    // Make connections ==============================================================

    // Connect external actions
    //this->connect(, this, SLOT(m_manipSupplier()));
}

void SupplierWidget::addSupplier()
{
    qDebug() << "Adding supplier...";

    SupplierActionDialog diag(this);

    if(diag.exec() == SupplierActionDialog::Accepted)
    {
        // Convert to SupplierTable, check this doesnt screw things up
        SupplierTable* table = (SupplierTable*)m_tableModel;
        if(!table->Insert(diag.data()))
            qDebug() << "Insert statement failed: SupplierWidget::addSupplier()";
            // TODO: Add popup thing
    }
}


void SupplierWidget::m_editAction(const QModelIndex &index)
{
    // Get data from table index
    SupplierTable::SupplierData data = { 0 };

    data.name = m_tableModel->data(m_tableModel->index(index.row(), (int)SupplierTable::NAME)).toString();


    SupplierActionDialog diag(this, data);

    if(diag.exec() == SupplierActionDialog::Accepted)
        qDebug() << "Dialog accepted";
}

SupplierWidget::~SupplierWidget()
{
}
