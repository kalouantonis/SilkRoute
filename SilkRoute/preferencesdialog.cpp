#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

#include <QtWidgets/QFileDialog>

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    this->connect(ui->btnBrowseDB, SIGNAL(clicked()), this, SLOT(m_browseFileSys()));
}

void PreferencesDialog::m_browseFileSys()
{
    QFileDialog diag(this, "Select DB!", "./", "*.db, *.sqlite");

    if(diag.exec() == QFileDialog::Accepted)
    {
        ui->lineEdit->setText(diag.directory().absolutePath() +
                              diag.selectedFiles()[0]);
    }
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}
