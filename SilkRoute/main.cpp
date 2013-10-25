#include "mainwindow.h"
#include "Users/logindialog.h"
#include "Database/dbconnector.h"

#include "Database/dbutils.h"

#include <QApplication>


// DB data
// TODO: Use function to parse settins file and locate DB name
const QString dbname = "data.sqlite";
// Contained in compiled resources
const QString schema_name = ":database/Resources/schema.sql";

const QString appName = "Silk Route Accounting";
const QString appVersion = "1.0.2";

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    // Set parameters for application
    app.setApplicationName(appName);
    app.setApplicationVersion(appVersion);

    // Create DB connection
    DB::DBConnector database;
    if(database.connect(dbname) != DB::CON_FAILED)
    {
        // Create all tables if they do not exist
        if(!DB::CreateAllTables(schema_name))
        {
            // Failed to create tables, quit

            QMessageBox::critical(NULL, "Database Error",
                                  "Database failed to initialize, please contact the nearest person and complain!",
                                  QMessageBox::Ok);

            return EXIT_FAILURE;
        }


        // Temp for testing
        bool admin = false;

        // Only allow login when testing PPD is not set
#ifndef _TESTING
        // Do login check before initializing main Window
        // Set parent as the main window
        LoginDialog loginDiag(NULL);


        // Make app process all events before app starts, give time for parsers, settings and db to finalize
        if(app.hasPendingEvents())
            app.processEvents();

        // Remove splash, show login dialog

        if(loginDiag.exec() == QDialog::Accepted)
        {

            // If admin property is super user
            admin = loginDiag.IsAdmin();
#else
            admin = true;
#endif

            MainWindow w(NULL, admin);

            w.show();
            return app.exec();

#ifndef _TESTING
        }
#endif
    }
    else
    {

        // Created in stack, so don't worry about not
        // referencing parent too much
        QMessageBox::critical(NULL, "Database connection failed",
                              "Connection to the databse has failed, please contact administrator..",
                              QMessageBox::Ok);
    }

        // Exit program
    app.quit();
}
