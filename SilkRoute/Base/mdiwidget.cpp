#include "mdiwidget.h"
#include "ui_mdiwidget.h"

namespace Base
{

MDIWidget::MDIWidget(QWidget *parent, DB::ITableModel* tableModel) :
    QWidget(parent),
    ui(new Ui::MDIWidget)
{
    ui->setupUi(this);

    attachModel(tableModel);

    // Set search validator, so as to avoid SQL Injections
    ui->txtSearch->setValidator(DB::ITable::GetAlNumValidator(this));

    // Resize all columns to fit contents
    ui->tableView->resizeColumnsToContents();

    // Make connections =================================================================
    //txtSearch
    this->connect(ui->txtSearch, SIGNAL(returnPressed()), this, SLOT(m_searchAction()));
    // Clear search, reset model
    this->connect(ui->btnClearSearch, SIGNAL(clicked()), this, SLOT(m_clearSearch()));
}

void MDIWidget::attachModel(DB::ITableModel *model)
{
    m_tableModel = model;

    // Attach model to view
    ui->tableView->setModel(m_tableModel);
}

void MDIWidget::m_searchAction()
{
    QString search = ui->txtSearch->text();

    if(!search.isEmpty())
    {
        m_tableModel->Search(search);

        // Exit function
        return;
    }

    m_tableModel->SelectAll();
}

void MDIWidget::m_clearSearch()
{
    // Clear txtSearch
    ui->txtSearch->clear();

    // Reset model
    m_tableModel->SelectAll();
}

void MDIWidget::m_editAction(const QModelIndex &)
{

}

MDIWidget::~MDIWidget()
{
    //delete m_tableModel;
    if(m_tableModel) // If not NULL
        delete m_tableModel;

    // Delete UI elements
    delete ui;
}

} // Namespace Base
