#ifndef REPORTGENERATEDIALOG_H
#define REPORTGENERATEDIALOG_H

#include <QDialog>
#include <SilkRoute/Reports/reporttable.h>

namespace Ui {
class ReportGenerateDialog;
}

/// Dialog to create a new report
class ReportGenerateDialog : public QDialog
{
    Q_OBJECT

public:
    /// Constructor, declares parent object
    explicit ReportGenerateDialog(QWidget *parent = 0);
    /// Destructor
    ~ReportGenerateDialog();

    /// Return data from dialogue to caller
    ReportTable::Data data() const;

private:
    /// Report dialog UI
    Ui::ReportGenerateDialog *ui;
};

#endif // REPORTGENERATEDIALOG_H
