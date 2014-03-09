#ifndef REPORTVIEW_H
#define REPORTVIEW_H

#include <SilkRoute/Base/mdiwidget.h>
#include <SilkRoute/Reports/reporttable.h>

/// Displays generated reports
class ReportView: public Base::MDIWidget
{
    Q_OBJECT

public:
    /// Constructor, sets parent object
    explicit ReportView(QWidget* parent = nullptr);
    /// Destructor
    ~ReportView();

    /// Returns object identifier
    static const QString& objectName() { return TAG; }

    /// Generates report and creates print dialog
    void generate();

public slots:
    /// Add new report
    virtual void add() override;
    /// Implement as empty. This functionality is not needed
    virtual void remove() override {}

private:
    /// Used for logging
    const static QString TAG;

    /// Date data used for report
    ReportTable::Data m_genData;
};

#endif // REPORTVIEW_H
