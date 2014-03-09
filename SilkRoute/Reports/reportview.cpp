#include "reportview.h"
#include "ui_mdiwidget.h"

#include <SilkRoute/Reports/reportgeneratedialog.h>
#include <SilkRoute/Base/currencyformatdelegate.h>

#include <KDReportsReport>
#include <KDReportsTextElement>
#include <KDReportsAutoTableElement>
#include <KDReportsPreviewDialog>

#include <QMessageBox>

const QString ReportView::TAG = "ReportView";

ReportView::ReportView(QWidget *parent)
    : Base::MDIWidget(parent, new ReportTable(nullptr))
{
    // Set object name for later identification
    this->setObjectName(ReportView::objectName());

    // Set window title
    this->setWindowTitle("Reports");

    // Hide search widgets. This view does not allow searching
    ui->lblSearch->hide();
    ui->btnClearSearch->hide();
    ui->txtSearch->hide();

    // Set delegate for revenue column
    // displaying data as formatted, localized currency
    ui->tableView->setItemDelegateForColumn(ReportTable::REVENUE,
                                new CurrencyFormatDelegate(ui->tableView));
    // Set delegate for cost column
    // displaying data as formatted, localized currency
    ui->tableView->setItemDelegateForColumn(ReportTable::COST,
                                new CurrencyFormatDelegate(ui->tableView));
    // Set delegate for profit column
    // displaying data as formatted, localized currency
    ui->tableView->setItemDelegateForColumn(ReportTable::PROFIT,
                                new CurrencyFormatDelegate(ui->tableView));
}

ReportView::~ReportView()
{
    // Empty destructor
}

void ReportView::generate()
{
    // Check if there are rows in model. If so, generate report
    if(m_tableModel->rowCount() > 0)
    {
        // Create report container
        KDReports::Report report;

        // Generate table element using the table model
        KDReports::AutoTableElement tableElement(m_tableModel);
        // Show vertical header
        tableElement.setVerticalHeaderVisible(true);

        // Title text
        KDReports::TextElement title;
        title.setText("Transaction Report");
        // Show in bold format
        title.setBold(true);
        // Underline text
        title.setUnderline(true);
        // Set font size to 20
        title.setPointSize(20);
        // Add title to report
        report.addElement(title);

        // Insert vertical spacing for easier reading
        report.addVerticalSpacing(2);

        // Text to display report date
        KDReports::TextElement date;
        // Insert to date
        date << "Date: " << m_genData.fromDate.toString();

        // Check if report is not daily
        if(!m_genData.daily)
            // Add to date
            date << " - " << m_genData.toDate.toString();

        // Insert date element in to report
        report.addElement(date);

        // Insert 10 mm vertical spacing
        report.addVerticalSpacing(10);

        // Insert table element
        report.addElement(tableElement);

        // Insert a further 10 mm vertical spacing
        report.addVerticalSpacing(10);

        // Get report sums
        ReportTable::Sums sums = static_cast<ReportTable*>(m_tableModel)
                ->GetSums(m_genData);

        // Check validity of data
        if(sums.cost == -1)
        {
            // Data invalid, notify user
            QMessageBox::critical(this, "Failed to generate report.",
                            "Report data is invalid.",
                             QMessageBox::Ok);
            // Exit function
            return;
        }


        // Total revenue text
        KDReports::TextElement revenueTotal;
        // insert total revenue values
        revenueTotal << "Total revenue: "
                // convert to localized currency format
                << QLocale::system().toCurrencyString(sums.revenue);


        // total cost text
        KDReports::TextElement costTotal;
        costTotal << "Total cost: "
                // convert to localized currency format
                << QLocale::system().toCurrencyString(sums.cost);

        // total profit text
        KDReports::TextElement profitTotal;
        profitTotal << "Total profit: "
                // convert to localized currency format
                << QLocale::system().toCurrencyString(sums.profit);


        // Add revenue total to report
        report.addElement(revenueTotal);
        // Add cost total to report
        report.addElement(costTotal);
        // Add profit total to report
        report.addElement(profitTotal);

        // Create preview dialog using report.
        KDReports::PreviewDialog preview(&report);

        // Show preview dialog
        preview.exec();
    }
    else    // No data in table model
    {
        // Notify user of error
        QMessageBox::warning(this, "No report generated.",
               "Please generate a report before attempting to print it.",
                QMessageBox::Ok);
    }
}

void ReportView::add()
{
    // Create new report dialog
    ReportGenerateDialog diag(this);

    // If ok button pressed
    if(diag.exec() == ReportGenerateDialog::Accepted)
    {
        // Set generated data from dialog
        m_genData = diag.data();
        // Cast model to ReportTable type and select data using the generated
        // data. It is safe to static_cast as we know the model is already
        // of type ReportTable
        static_cast<ReportTable*>(m_tableModel)->Select(m_genData);

        // Resize table view columns to fit contents
        ui->tableView->resizeColumnsToContents();
    }
}
