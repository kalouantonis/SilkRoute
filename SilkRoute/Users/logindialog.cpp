#include "logindialog.h"
#include "ui_logindialog.h"

#include <QSqlError>
#include <QSqlRecord>
#include <QSqlResult>

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

    // Set admin rights to false
    m_isAdmin = false;

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
#ifdef _DEBUG
    qDebug() << "Login button pressed: "
             << m_loginAttempts + 1
             << " attempts\n";
#endif

    if(ui->txtUser->text().isEmpty() ||
            ui->txtPass->text().isEmpty())
    {
#ifdef _DEBUG
        qDebug() << "No data entered in login fields";
#endif

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
                              "There was an error in the database, please consult developer",
                              QMessageBox::Ok);
        qDebug() << userTable.GetLastError();

        // Quit
        this->reject();
    }
    else if(res != RES_NONE)
    {
#ifdef _DEBUG
        qDebug() << "Login credentials correct";
#endif

        if(res == RES_SUPERUSER)
            m_isAdmin = true;

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
