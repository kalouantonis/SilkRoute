#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWorkspace>
#include <QSignalMapper>

#include <QMessageBox>

// My includes
#include <SilkRoute/preferencesdialog.h>
#include <SilkRoute/Suppliers/supplierwidget.h>
#include <SilkRoute/Stock/stockwidget.h>
#include <SilkRoute/Base/mdiwidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0, bool admin = false);
    ~MainWindow();
    
private slots:
    // Called when fullscreen is toggled
    void OnFullscreenAction(bool checked);

    // Create all toolbar and menu actions
    void m_createActions();

    // view actions ====================================
    void m_createSupplierView();
    void m_createTransactionView() {}
    void m_createStockView();

    // Add actions
    void m_addSupplierAction();

    void m_showPreferences();


private:
    // Called when any event invokes a close,
    // so that I can check if user wishes to quit
    void closeEvent(QCloseEvent*);

    // Create toolbar items
    void m_initToolbar();

    Ui::MainWindow *ui;

    // Widgets that may need to be activated
    SupplierWidget* m_supplierWidget;
    StockWidget* m_stockWidget;

    // used when creating widget
    enum WidgetIDS
    {
        SUPPLIER,
        TRANSACTION,
        STOCK
    };

    // Will add widget to MDI, if it exists, it will check if active
    // if not, it will activate
    // Send pointer to pointer, so as the actual address of widget is exploited
    void m_createWidget(const WidgetIDS id, QWidget** widget);
};

#endif // MAINWINDOW_H
