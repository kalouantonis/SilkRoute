#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent, bool admin) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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

template<typename T>
T* MainWindow::m_createWidget()
{
    // Initialize as nothing, just because RAII
    T* widget = NULL;

    // Check if current widget is already of this type
    if(this->centralWidget()->objectName() != T::objectName())
    {
#ifdef _DEBUG
        qDebug() << "Creating " << T::objectName() << "...";
#endif

        // Allocate new widget of type T
        widget = new T(this);

        // Set as central widget
        this->setCentralWidget(widget);
    }
    else
        // Grab central widget, it is desired type, widget is already shown
        widget = (T*)this->centralWidget();

    // Check that widget is not NULL, if so, memory errors, get a new PC
    assert(widget != NULL);

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
    //SupplierWidget* widget = qobject_cast<SupplierWidget*>(m_createWidget(SUPPLIER));
    SupplierWidget* widget = m_createWidget<SupplierWidget>();

    widget->addSupplier();
}

void MainWindow::m_createStockView()
{
    //m_createWidget(STOCK);
    m_createWidget<StockWidget>();
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
