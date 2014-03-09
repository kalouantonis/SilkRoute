#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
//#include <QWorkspace>
#include <QSignalMapper>

#include <QtWidgets/QMessageBox>

// My includes
#include <SilkRoute/preferencesdialog.h>
#include <SilkRoute/Suppliers/supplierwidget.h>
#include <SilkRoute/Stock/stockwidget.h>
#include <SilkRoute/Types/typeswidget.h>
#include <SilkRoute/Base/mdiwidget.h>

// Debugging
#include <cassert>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    // Called when fullscreen is toggled
    void OnFullscreenAction(bool checked);

    // view actions ====================================
    void m_createSupplierView();
    void m_createTransactionView();
    void m_createStockView();
    void m_createTypeView();
    void m_createGenReportView();
    void m_printReport();

    // Add actions
    void m_addSupplierAction();
    void m_addStockAction();
    void m_addTransactionAction();
    void m_addTypeAction();

    // Remove actions
    void m_removeSupplierAction();
    void m_removeTypeAction();
    void m_removeStockAction();

    void m_showPreferences();
private:
    // Used for logging
    static const QString TAG;

    // Called when any event invokes a close,
    // so that I can check if user wishes to quit
    void closeEvent(QCloseEvent*);

    // Create all toolbar and menu actions
    void m_createActions();

    Ui::MainWindow *ui;

    // Widget factory using template meta-programming for simplicity/keeping things generic
    template<typename T>
    T* m_createWidget();
};

#endif // MAINWINDOW_H
