#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent, bool admin) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_supplierWidget(NULL)
{
    ui->setupUi(this);

    // Give user information that the app is ready to be used
    //ui->statusBar->setStatusTip(tr("Ready..."));

    // Hide admin panel... for now
    ui->groupAdmin->setHidden(!admin);

    m_createActions();
}

void MainWindow::m_createActions()
{
    // Link actions to events
    this->connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(OnExit()));

    // Link fullscreen check
    this->connect(ui->actionFullscreen, SIGNAL(triggered(bool)), this, SLOT(OnFullscreenAction(bool)));

    // Preferences link
    this->connect(ui->actionPreferences, SIGNAL(triggered()), this,
                  SLOT(m_showPreferences()));

    // Link view actions
    this->connect(ui->actionView_Suppliers, SIGNAL(triggered()), this,
                  SLOT(m_createSupplierView()));
    this->connect(ui->actionView_Stock, SIGNAL(triggered()), this,
                SLOT(m_createStockView()));
    this->connect(ui->actionView_Transactions, SIGNAL(triggered()), this,
                  SLOT(m_createTransactionView()));


    // COnnect side bar buttons
    this->connect(ui->btnSupView, SIGNAL(clicked()), this,
                  SLOT(m_createSupplierView()));
}

void MainWindow::m_initToolbar()
{

}

void MainWindow::m_showPreferences()
{
    PreferencesDialog prefDiag(this);

    if(prefDiag.exec() == PreferencesDialog::Accepted)
    {
        // Save preferences

#ifdef _DEBUG
        qDebug() << "Preferences accepted";
#endif
    }
}

void MainWindow::m_createWidget(const WidgetIDS id, QWidget **widget)
{

    if(!(*widget))
    {
        // Find ID and create appropriate widget
        switch(id)
        {
        case SUPPLIER:
            (*widget) = new SupplierWidget(this);
            break;
        case TRANSACTION:
            break;
        case STOCK:
            break;
        }
        // Subscribe sub-window
        ui->mdiArea->addSubWindow(*widget);

        // Show window maximized
        (*widget)->showMaximized();
    }
    else if(!(*widget)->isActiveWindow())
    {
        // If not active, but exists, set as active
        ui->mdiArea->setActiveSubWindow((QMdiSubWindow*)(*widget));
    }

}

void MainWindow::m_createSupplierView()
{
#ifdef _DEBUG
    qDebug() << "Creating supplier view";
#endif

    // Create the supplier widget
    m_createWidget(SUPPLIER, (QWidget**)&m_supplierWidget);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Create message box, inquire about quiting
    QMessageBox tempQuitMsg(QMessageBox::Warning, "Quit?",
                            "Are you sure you want to quit?",
                            QMessageBox::Yes | QMessageBox::No, this);

    if(tempQuitMsg.exec() == QMessageBox::Yes)
    {
        // Quit confirmed, save and quit

        // TODO: Save stuff and close open documents

        // Accept event, quit
        event->accept();
    }
    else
        // Ignore event, pretend nothing happened...
        // let's not talk about this again, ok?
        event->ignore();
}

void MainWindow::OnFullscreenAction(bool checked)
{
    if(!checked)
        this->showNormal();
    else
        this->showFullScreen();
}

void MainWindow::OnExit()
{
    this->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
