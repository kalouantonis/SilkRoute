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

void SupplierWidget::m_manipSupplier()
{
    SupplierActionDialog diag;

    if(diag.exec() == SupplierActionDialog::Accepted)
        qDebug() << "Dialog accepted with data: " << diag.data();
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
