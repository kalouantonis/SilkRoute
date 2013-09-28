#ifndef SUPPLIERWIDGET_H
#define SUPPLIERWIDGET_H

#include <QWidget>

namespace Ui {
class SupplierWidget;
}

class SupplierWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SupplierWidget(QWidget *parent = 0);
    ~SupplierWidget();
    
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
};

#endif // SUPPLIERWIDGET_H
