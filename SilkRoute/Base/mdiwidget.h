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

/*
namespace Ui {
class MDIWidget;
}*/

namespace Base
{

class MDIWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MDIWidget(QWidget *parent, DB::ITableModel* tableModel = NULL);
    ~MDIWidget();
    
protected:
    //Ui::MDIWidget *ui;

    DB::ITableModel* m_tableModel;

    // View Items ==============================
    QPushButton* m_btnClearSearch;
    QTableView* m_tableView;
    QLineEdit* m_txtSearch;
    QSpacerItem* m_spacer;
};

} // namespace Base

#endif // MDIWIDGET_H
