#ifndef MDIWIDGET_H
#define MDIWIDGET_H

#include <QWidget>

#include <SilkRoute/Database/itable.h>
#include <SilkRoute/Database/itablemodel.h>

#include <QLineEdit>
#include <QTableView>
#include <QPushButton>
#include <QSpacerItem>
#include <QLayout>
#include <QCloseEvent>

namespace Ui {
class MDIWidget;
}

namespace Base
{

const QString MDIObjectName = "MDIWidget";

class MDIWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MDIWidget(QWidget *parent = NULL, DB::ITableModel* model = NULL);
    virtual ~MDIWidget();

    void attachModel(DB::ITableModel* model);

private slots:
    // Used by search text widget to find records
    void m_searchAction();

    // Clear button clicked
    void m_clearSearch();

    // Edit actions
    virtual void m_editAction(const QModelIndex& index);
    
protected:
    Ui::MDIWidget *ui;

    // Polymorphic Table container
    // Model for grabbing data from SQL
    DB::ITableModel* m_tableModel;

private:
    void closeEvent(QCloseEvent*);
};

} // namespace Base

#endif // MDIWIDGET_H
