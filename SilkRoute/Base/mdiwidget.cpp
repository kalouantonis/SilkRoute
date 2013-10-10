#include "mdiwidget.h"
#include "ui_mdiwidget.h"

namespace Base
{

MDIWidget::MDIWidget(QWidget *parent, DB::ITableModel* tableModel) :
    QWidget(parent),
    m_tableModel(tableModel)
    //ui(new Ui::MDIWidget)
{
    //ui->setupUi(this);
    m_txtSearch = new QLineEdit(this);
    m_tableView = new QTableView(this);
    m_btnClearSearch = new QPushButton("Clear", this);
}

MDIWidget::~MDIWidget()
{
    //delete m_tableModel;
    if(m_tableModel) // If not NULL
        delete m_tableView;


    // Delete UI elements
    delete m_txtSearch;
    delete m_tableView;
    delete m_btnClearSearch;
    //delete ui;
}

} // Namespace Base
