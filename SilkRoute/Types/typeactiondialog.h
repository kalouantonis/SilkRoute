#ifndef TYPEACTIONDIALOG_H
#define TYPEACTIONDIALOG_H

#include <QDialog>
#include "typestable.h"

namespace Ui {
class TypeActionDialog;
}

class TypeActionDialog : public QDialog
{
    Q_OBJECT

public:
    /// Constructor, setting parent object
    explicit TypeActionDialog(QWidget *parent = nullptr);
    /// Constructor, setting parent object and data to fill dialog with
    explicit TypeActionDialog(QWidget *parent, const TypesTable::Data& data);
    /// Destructor
    ~TypeActionDialog();

    /// Return data contained in text fields
    TypesTable::Data data() const;

    /// Sets data in text field
    void setData(const TypesTable::Data& data);

private slots:
    /// called when description is changed and updates reference value
    void completeRef(const QString& val);
    /// Called when dialog OK button is clicked
    void okBtnClicked();

private:
    /// Common function for constructors to call
    void construct();

    /// Dialog user interface instance
    Ui::TypeActionDialog *ui;
};

#endif // TYPEACTIONDIALOG_H
