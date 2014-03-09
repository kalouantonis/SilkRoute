#include "mainwindow.h"
#include "Users/logindialog.h"
#include "Database/dbconnector.h"

#include "Database/dbutils.h"
#include <SilkRoute/Utils/Logger.h>

#include <QtWidgets/QApplication>

// Database file name
const QString dbname = "data.sqlite";
// Contained in compiled resources
const QString schema_name = ":database/Resources/schema.sql";

// Application data
const QString appName = "Silk Route Accounting";
const QString appVersion = "1.1.53";


// Program entry point
int main(int argc, char** argv)
{

#ifdef _DEBUG
    // Set level to debug if preprocessor symbol _DEBUG is set by compiler
    // So, only show debug messages when program is compiled in debug mode
    setLogLevel(DEBUG);
#endif

    QApplication app(argc, argv);
    // Set parameters for application
    app.setApplicationName(appName);
    app.setApplicationVersion(appVersion);

    QSettings settings("SilkRoute", appName, NULL);

    QString db_location = settings.value("db_location", dbname).toString();

    // Create DB connection
    DB::DBConnector database;

    int ret = database.connect(db_location);

    // Check if connection to database succeeded
    if(ret != DB::CON_FAILED)
    {
        // Create all tables if they do not exist
        if(!DB::CreateAllTables(schema_name))
        {
            // Failed to create tables, quit

            QMessageBox::critical(NULL, "Database Error",
                                  "Database failed to initialize, "
                                  "please consult the user manual.",
                                  QMessageBox::Ok);

            // Return exit failure message to OS
            return EXIT_FAILURE;
        }


        // Only allow login when testing PPD is not set
#ifndef _TESTING
        // Do login check before initializing main Window
        // Set parent as the main window
        LoginDialog loginDiag(NULL);


        // Make app process all events before app starts, give time for parsers, settings and db to finalize
        if(app.hasPendingEvents())
            app.processEvents();

        if(loginDiag.exec() == QDialog::Accepted)
        {

#endif

            // Create main window
            MainWindow w(nullptr);

            // Show main window to user
            w.show();
            // Execute application
            return app.exec();

#ifndef _TESTING
        }
#endif
    }
    else if(ret == DB::CON_INVALID)
    {
        QMessageBox::critical(NULL, "Database corrupted.",
                              "Database file has been corrupted. "
                              "To fix see user manual or delete database file.",
                              QMessageBox::Ok);
    }
    else
    {

        // Created in stack, so don't worry about not
        // referencing parent too much
        QMessageBox::critical(NULL, "Database connection failed",
                              "Connection to the database has failed, please contact administrator..",
                              QMessageBox::Ok);
    }

        // Exit program
    app.quit();

    // Return exit failure message to OS
    return EXIT_FAILURE;
}
