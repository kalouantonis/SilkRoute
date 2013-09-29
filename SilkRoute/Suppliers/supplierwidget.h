#ifndef SUPPLIERWIDGET_H
#define SUPPLIERWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class SupplierWidget;
}

class SupplierWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SupplierWidget(QWidget *parent = 0);
    ~SupplierWidget();

public slots:
    void searchAction();
    
private:
    Ui::SupplierWidget *ui;

    // TODO: Move to suppliertable
    // Provides enums for column access, keep stuff simple
    enum SUP_COLUMNS
    {
        ID,
        NAME,
        PROFIT,
        EXPENDITURE,
        LAST_TRANSACTION
    };

    // Model for data grabbing from SQL
    QSqlQueryModel m_supplierModel;
};

#endif // SUPPLIERWIDGET_H
