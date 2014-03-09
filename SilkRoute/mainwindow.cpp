#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "SilkRoute/Transactions/transactionwidget.h"
#include <SilkRoute/Types/typeswidget.h>
#include <SilkRoute/Utils/Logger.h>
#include <Reports/reportgeneratedialog.h>
#include <SilkRoute/Reports/reportview.h>

#include <QCloseEvent>

const QString MainWindow::TAG = "MainWindow";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Give user information that the app is ready to be used
    ui->statusBar->setStatusTip(tr("Ready..."));

    // Hide admin panel... for now
    //ui->groupAdmin->setHidden(!admin);

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
    this->connect(ui->btnTransView, SIGNAL(clicked()), this,
                  SLOT(m_createTransactionView()));
    this->connect(ui->btnTypeView, SIGNAL(clicked()), this,
                  SLOT(m_createTypeView()));
    this->connect(ui->btnGenReport, SIGNAL(clicked()), this,
                  SLOT(m_createGenReportView()));
    this->connect(ui->btnPrintReport, SIGNAL(clicked()), this,
                  SLOT(m_printReport()));

    // Add
    this->connect(ui->btnSupAdd, SIGNAL(clicked()), this, SLOT(m_addSupplierAction()));
    this->connect(ui->btnStockAdd, SIGNAL(clicked()), this, SLOT(m_addStockAction()));
    this->connect(ui->btnTransAdd, SIGNAL(clicked()), this, SLOT(m_addTransactionAction()));
    this->connect(ui->btnTypeAdd, SIGNAL(clicked()), this, SLOT(m_addTypeAction()));

    // Remove
    this->connect(ui->btnSupRemove, SIGNAL(clicked()), this, SLOT(m_removeSupplierAction()));
    this->connect(ui->btnTypeRemove, SIGNAL(clicked()), this, SLOT(m_removeTypeAction()));
    this->connect(ui->btnStockRemove, SIGNAL(clicked()), this, SLOT(m_removeStockAction()));
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

template<typename T>
T* MainWindow::m_createWidget()
{
    // Initialize as nothing, just because RAII
    T* widget = NULL;

    // Check if current widget is already of this type
    if(this->centralWidget()->objectName() != T::objectName())
    {
        debug(TAG, "Creating " + T::objectName() + "...");

        // Allocate new widget of type T
        widget = new T(this);

        // Set as central widget
        this->setCentralWidget(widget);
    }
    else
    {
        // Grab central widget, it is desired type, widget is already shown
        widget = (T*)this->centralWidget();
    }

    // Check that widget is not NULL, if so, memory errors, get a new PC
    assert(widget != NULL);

    // Maximize selected widget
    widget->showMaximized();

    return widget;
}

void MainWindow::m_createSupplierView()
{
    // Create the supplier widget
    //m_createWidget(SUPPLIER);
    m_createWidget<SupplierWidget>();
}

void MainWindow::m_addSupplierAction()
{
    // if window is not created, do it, if it is, set to active
    // So no worries, we arent allocating a new widget every click of add
    SupplierWidget* widget = m_createWidget<SupplierWidget>();

    widget->add();
}

void MainWindow::m_addStockAction()
{
    StockWidget* widget = m_createWidget<StockWidget>();

    widget->add();
}

void MainWindow::m_addTransactionAction()
{
    TransactionWidget* widget = m_createWidget<TransactionWidget>();

    widget->add();
}

void MainWindow::m_addTypeAction()
{
    TypesWidget* widget = m_createWidget<TypesWidget>();

    widget->add();
}

void MainWindow::m_removeSupplierAction()
{
    SupplierWidget* widget = m_createWidget<SupplierWidget>();

    widget->remove();
}

void MainWindow::m_removeTypeAction()
{
    TypesWidget* widget = m_createWidget<TypesWidget>();

    widget->remove();
}

void MainWindow::m_removeStockAction()
{
    StockWidget* widget = m_createWidget<StockWidget>();

    widget->remove();
}

void MainWindow::m_createStockView()
{
    //m_createWidget(STOCK);
    m_createWidget<StockWidget>();
}

void MainWindow::m_createTransactionView()
{
    m_createWidget<TransactionWidget>();
}

void MainWindow::m_createTypeView()
{
    m_createWidget<TypesWidget>();
}

void MainWindow::m_createGenReportView()
{
    auto reportView = m_createWidget<ReportView>();
    reportView->add();
}

void MainWindow::m_printReport()
{
    auto reportView = m_createWidget<ReportView>();
    reportView->generate();
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
