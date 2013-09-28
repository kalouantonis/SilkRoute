#include "supplierwidget.h"
#include "ui_supplierwidget.h"

#include <QSqlTableModel>
#include <QSqlQueryModel>

SupplierWidget::SupplierWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupplierWidget)
{
    ui->setupUi(this);

    QSqlQueryModel* model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM suppliers");

    // Set header data
    model->setHeaderData(ID, Qt::Horizontal, QObject::tr("Ref"));
    model->setHeaderData(NAME, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(PROFIT, Qt::Horizontal, QObject::tr("Profit"));
    model->setHeaderData(EXPENDITURE, Qt::Horizontal, QObject::tr("Expenditure"));
    // Allow clicking to open transaction window
    model->setHeaderData(LAST_TRANSACTION, Qt::Horizontal, QObject::tr("Last Transaction"));

    // Set model delegate
    ui->tableView->setModel(model);

    // Resize transaction header so as to look nice
    ui->tableView->setColumnWidth(LAST_TRANSACTION, ui->tableView->columnWidth(LAST_TRANSACTION) + 10);

}

SupplierWidget::~SupplierWidget()
{
    delete ui;
}
