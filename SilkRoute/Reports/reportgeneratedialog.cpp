#include "reportgeneratedialog.h"
#include "ui_reportgeneratedialog.h"

ReportGenerateDialog::ReportGenerateDialog(QWidget *parent) :
    QDialog(parent),                    // Parent constructor
    ui(new Ui::ReportGenerateDialog)    // UI constructor
{
    // initialize UI
    ui->setupUi(this);

    // Set fromDate to current date
    ui->fromDate->setDate(QDate::currentDate());
    // Set toDate to the day after current date
    ui->toDate->setDate(QDate::currentDate().addDays(1));
}

ReportGenerateDialog::~ReportGenerateDialog()
{
    // De-allocate UI from heap memory
    delete ui;
}

ReportTable::Data ReportGenerateDialog::data() const
{
    // Create new data container
    ReportTable::Data data;

    // Insert from date in to data container
    data.fromDate = ui->fromDate->date();
    // Insert if daily report is needed in to data container.
    // Use ternary operator to convert framework checked value in to
    // true or false
    data.daily = ui->chkDaily->checkState() == Qt::Checked ? true : false;
    // If report is not a daily one
    if(!data.daily)
        // Set to date using ui selection box
        data.toDate = ui->toDate->date();

    // return data container to caller
    return data;
}
