#ifndef MDIWIDGET_H
#define MDIWIDGET_H

#include <QtWidgets/QWidget>

#include <SilkRoute/Database/itablemodel.h>

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QLayout>
#include <QCloseEvent>

namespace Ui {
class MDIWidget;
}

namespace Base
{

class MDIWidget : public QWidget
{
    Q_OBJECT

public:
    /// Constructor, must be called explicitly.
    /// Sets the parent caller and required table model used in displaying
    /// given database data. Set to NULL by default
    explicit MDIWidget(QWidget *parent = nullptr, DB::ITableModel* model = nullptr);
    /// Destructor. Called when object is destroyed
    virtual ~MDIWidget();

    /// Get current object name
    static const QString objectName() { return TAG; }

public slots:
    /// Pure Virtual, must be implemented by inheritor
    /// Called when a new item needs to be added
    virtual void add() = 0;
    /// Called when item needs to be removed
    virtual void remove();

private slots:
    /// Used by search text widget to find records
    void m_searchAction();

    /// Clear button clicked
    void m_clearSearch();

    /// Called internally when edit is requested
    virtual void m_editAction(const QModelIndex& index);
    
protected:
    /// The user interface
    Ui::MDIWidget *ui;

    /// Polymorphic Table container
    /// model for grabbing data from SQL
    DB::ITableModel* m_tableModel;

private:
    /// Attach a model to this object instance
    void attachModel(DB::ITableModel* model);

    /// Used for logging
    const static QString TAG;
};

} // namespace Base

#endif // MDIWIDGET_H
