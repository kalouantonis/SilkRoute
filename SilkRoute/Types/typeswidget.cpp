#include <SilkRoute/Types/typeswidget.h>
#include <SilkRoute/Types/typestable.h>
#include <SilkRoute/Types/typeactiondialog.h>
#include "ui_mdiwidget.h"

#include <QDebug>
#include <QMessageBox>

#include <SilkRoute/Utils/Logger.h>

TypesWidget::TypesWidget(QWidget *parent)
    : Base::MDIWidget(parent, new TypesTable(nullptr))
{
    this->setObjectName(objectName());

    ui->tableView->hideColumn(TypesTable::ID);

    this->setWindowTitle(tr("Types"));
}

TypesWidget::~TypesWidget()
{

}

void TypesWidget::add()
{
    info(TypesObjectName, "Adding types...");

    TypeActionDialog diag(this);

    TypesTable* table = static_cast<TypesTable*>(m_tableModel);

    // I know goto's are bad, but meh, i dont care right now
re_enter:

    if(diag.exec() == TypeActionDialog::Accepted)
    {
        TypesTable::Data data = diag.data();

        if(!table->RefExists(data.ref))
        {
            if(!table->Insert(data))
            {
                error(TypesObjectName, "Record insertion failed");
            }
        }
        else
        {
            QMessageBox::warning(this, "Reference already exists!",
                                     "Please enter a different reference ID.", QMessageBox::Ok);

            diag.setData(data);
            goto re_enter;
        }
    }
}

void TypesWidget::m_editAction(const QModelIndex &index)
{
    TypesTable::Data data;

    int usedRow = index.row();

    // Fill previous data
    data.id = m_tableModel->data(m_tableModel->index(usedRow, (int)TypesTable::ID)).toInt();
    data.ref = m_tableModel->data(m_tableModel->index(usedRow, (int)1)).toString();
    data.description = m_tableModel->data(m_tableModel->index(usedRow, (int)TypesTable::DESCRIPTION)).toString();

    TypeActionDialog diag(this, data);

    if(diag.exec() == TypeActionDialog::Accepted)
    {
        TypesTable* table = static_cast<TypesTable*>(m_tableModel);

        // Modify description with dialog description
        data.description = diag.data().description;

        if(!table->Update(data))
        {
            error(TypesObjectName, "Failed to update record: " + data.ref);
            // Some popup or something
        }
    }
}
