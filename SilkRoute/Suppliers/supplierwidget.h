#ifndef SUPPLIERWIDGET_H
#define SUPPLIERWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>

// For table actions
#include <QModelIndex>

// My includes
#include <SilkRoute/Suppliers/supplieractiondialog.h>
#include <SilkRoute/Suppliers/suppliertable.h>

namespace Ui {
class SupplierWidget;
}

class SupplierWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SupplierWidget(QWidget *parent = 0);
    ~SupplierWidget();

signals:
    // Called when supplier manipulation is required
    void addSupplierAction();

private slots:
    void m_searchAction();
    void m_clearSearch();

    // Supplier manipulations
    void m_manipSupplier();

    void m_editAction(const QModelIndex& index);

private:
    Ui::SupplierWidget *ui;

    // Model for data grabbing from SQL
    // TODO: Implement as QSqlRelationalTableModel()
    SupplierTable* m_supplierModel;

    // Supplier manipulation dialog
    //SupplierActionDialog* m_supDiag;
};

#endif // SUPPLIERWIDGET_H
