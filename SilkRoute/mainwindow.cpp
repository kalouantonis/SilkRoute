#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent, bool admin) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_supplierWidget(NULL),
    m_stockWidget(NULL)
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

    // Link to default close action
    this->connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

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

    // Connect side bar buttons =========================================================
    // Views
    this->connect(ui->btnSupView, SIGNAL(clicked()), this,
                  SLOT(m_createSupplierView()));
    this->connect(ui->btnStockView, SIGNAL(clicked()), this,
                  SLOT(m_createStockView()));

    // Add
    this->connect(ui->btnSupAdd, SIGNAL(clicked()), this, SLOT(m_addSupplierAction()));
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

void MainWindow::m_createWidget(const WidgetIDS id, Base::MDIWidget **widget)
{
#ifdef _DEBUG
        qDebug() << "Creating widget...";
#endif

        const QString currWidgetName = this->centralWidget()->objectName();

        // Find ID and create appropriate widget
        switch(id)
        {
        case SUPPLIER:
            if(currWidgetName != SupplierObjectName)
                (*widget) = new SupplierWidget(this);
            break;
        case TRANSACTION:
            break;
        case STOCK:
            if(currWidgetName != StockObjectName)
                (*widget) = new StockWidget(this);
            break;
        default:
            // Create empty widget so as to avoid segfaults through
            // NULL pointer dereferencing
            (*widget) = new Base::MDIWidget(this);
        }
        // Subscribe sub-window
        //ui->mdiArea->addSubWindow(*widget);

        // Display new widget
        (*widget)->showMaximized();

        this->setCentralWidget(*widget);

    /*else if(!(*widget)->isTopLevel())
    {
#ifdef _DEBUG
        qDebug() << "Widget already exists but not active, setting as active";
#endif

        // If not active, but exists, set as active
        (*widget)->setFocus();
    }*/

}

void MainWindow::m_createSupplierView()
{
    // Create the supplier widget
    // TODO: Use dynamic_cast or static_cast
    //m_createWidget(SUPPLIER, (Base::MDIWidget**)&m_supplierWidget);
    //m_supplierWidget = new SupplierWidget(this);
    //m_supplierWidget->showMaximized();

    //this->setCentralWidget(m_supplierWidget);
    m_createWidget(SUPPLIER, (Base::MDIWidget**)&m_supplierWidget);
}

void MainWindow::m_addSupplierAction()
{
    // if window is not created, do it, if it is, set to active
    //m_createWidget(SUPPLIER, (Base::MDIWidget**)&m_supplierWidget);

    // Call signal, the widget handles the rest
    //emit m_supplierWidget->addSupplierAction();

}

void MainWindow::m_createStockView()
{
    m_createWidget(STOCK, (Base::MDIWidget**)&m_stockWidget);
    m_stockWidget = new StockWidget(this);

    m_stockWidget->showMaximized();

    this->setCentralWidget(m_stockWidget);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Only check when testing mode is not on
#ifndef _TESTING
    // Create message box, inquire about quiting
    QMessageBox tempQuitMsg(QMessageBox::Warning, "Quit?",
                            "Are you sure you want to quit?",
                            QMessageBox::Yes | QMessageBox::No, this);

    if(tempQuitMsg.exec() == QMessageBox::Yes)
    {
        // Quit confirmed, save and quit

        // TODO: Save stuff and close open documents
#endif

        // Close all subwindows

        // Accept event, quit
        event->accept();
#ifndef _TESTING
    }
    else
        // Ignore event, pretend nothing happened...
        // let's not talk about this again, ok?
        event->ignore();
#endif
}

void MainWindow::OnFullscreenAction(bool checked)
{
    if(!checked)
        this->showNormal();
    else
        this->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}
