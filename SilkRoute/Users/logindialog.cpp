#include "logindialog.h"
#include "ui_logindialog.h"

#include <QSqlError>
#include <QSqlRecord>
#include <QSqlResult>

#include <SilkRoute/Utils/Logger.h>

const QString LoginDialog::TAG = "LoginDialog";

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
  , userTable(parent)
{
    m_Construct();
}

void LoginDialog::m_Construct()
{
    // Create UI in memory
    ui = new Ui::LoginDialog;

    // Initialize login attempts
    m_loginAttempts = 0;

    // Initialize UI
    ui->setupUi(this);

    // Set password field to hide characters
    ui->txtPass->setEchoMode(QLineEdit::Password);

    // Set warning to hidden by default
    ui->lblCWarn->setHidden(true);

    // Resize dialog to fit warning label
    this->resize(this->size().width(),
                 this->size().height() - ui->lblCWarn->height());

    // Has not been resized by login failure yet
    m_resized  = false;

    // Set focus to user input text field
    ui->txtUser->setFocus();

    // Connect btnLogin click to handler
    this->connect(ui->btnLogin, SIGNAL(clicked()), this, SLOT(LoginBtnPressed()));

    this->connect(ui->btnExit, SIGNAL(clicked()), this, SLOT(ExitBtnPressed()));
}

void LoginDialog::LoginBtnPressed()
{
    debug(TAG, "Login button pressed: "
             + QString::number(m_loginAttempts + 1)
             + " attempts\n");

    if(ui->txtUser->text().isEmpty() ||
            ui->txtPass->text().isEmpty())
    {
        debug(TAG, "No data entered in login fields");

        // No fields were filed in
        QMessageBox::information(this, "Please enter all details",
                                 "You must fill in all fields before attempting to log in!",
                                 QMessageBox::Ok);

    }

    // Result from user query
    USERTABLE_RETURN res = userTable.IsValidLogin(ui->txtUser->text(), ui->txtPass->text());

    if(res == RES_FAILED)
    {
        // TODO: Handle Error

        // Critical message, query failed for some reason
        QMessageBox::critical(this, "Database Error",
                              "There was an error in the database, please consult the developer",
                              QMessageBox::Ok);
        error(TAG, userTable.GetLastError());

        // Quit
        this->reject();
    }
    else if(res != RES_NONE)
    {
        debug(TAG, "Login credentials correct");

        // Login credential correct
        this->accept();
    }
    // Check login attempts again max allowed
    else if(m_loginAttempts++ >= MAXLOG_ATTEMPTS - 1)
    {
        // Create temp dialog to display error message
        QMessageBox::critical(this, "Login failed",
                              "You have reached the maximum allowed login attempts",
                              QMessageBox::Ok);
        // Exit
        this->reject();
    }
    else
    {
        // Login failed, but still have attempts left

        if(!m_resized)
        {
            // Don't want to repeat ourselves now do we?
            m_resized = true;

            // Show the warning message
            ui->lblCWarn->setHidden(false);
            // Resize dialog height to fit label width
            this->resize(this->size().width(),
                         this->size().height() + ui->lblCWarn->geometry().height());
        }

        // Clear password field
        ui->txtPass->clear();

        // Reset focus to the user input
        ui->txtUser->setFocus();
        // Select all text for re-entry
        ui->txtUser->selectAll();
    }

}

void LoginDialog::ExitBtnPressed()
{
    // Dialog sends reject message, program exits
    this->reject();
}


LoginDialog::~LoginDialog()
{
    delete ui;
}
