#ifndef TRANSACTIONACTIONDIALOG_H
#define TRANSACTIONACTIONDIALOG_H

#include "transactiontable.h"
#include <SilkRoute/Stock/stocktable.h>

#include <QTableWidgetItem>
#include <QDialog>

namespace Ui {
class TransactionActionDialog;
}

class TransactionActionDialog : public QDialog
{
    Q_OBJECT

public:
    /// Constructor, setting parent object and stock model
    explicit TransactionActionDialog(QWidget *parent, StockTable* stockTable);
    /// Constructor, setting parent object, required models and
    /// data to fill dialog with
    explicit TransactionActionDialog(QWidget *parent, StockTable *stockTable, const QVector<TransactionTable::Data>& data);
    /// Destructor
    ~TransactionActionDialog();

    /// Get dialog data
    QVector<TransactionTable::Data> data() const;

    /// Set the dialog data.
    void setData(const QVector<TransactionTable::Data>& data);

private slots:
    /// Insert transaction row in to table
    int m_addTrans();
    /// Remove transaction row from table
    void m_removeTrans();

private:
    /// Constructor delegate. Called by both constructors
    void construct();

    /// Transaction table columns
    enum COLUMNS
    {
        ID = 0,         /// Transaction ID
        STOCK_ITEM,     /// Related stock item
        AMOUNT,         /// Currency amount
        POS_NEG,        /// Positive or negative stock amount
        NO_SOLD,        /// Number of items sold
        DELETED         /// If item is deleted
    };

    /// Stock model reference
    StockTable* m_stockTable;

    /// Dialog user interface instance
    Ui::TransactionActionDialog *ui;
};

/// Exception that is called when invalid amounts are entered
/// in to the dialog
class InvalidAmountException: public std::runtime_error
{
public:
    /// Constructor, takes standard c-style string
    InvalidAmountException(const char* m = "Invalid amount entered")
        : std::runtime_error(m) // Parent constructor
    {
    }

    /// Constructor, takes qt style string
    InvalidAmountException(const QString& m)
        : std::runtime_error(m.toStdString()) // Parent constructor
    {
    }
};

#endif // TRANSACTIONACTIONDIALOG_H
