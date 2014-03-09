#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QtWidgets/QDialog>
// For debugging, dur...
#include <QDebug>

// For messaging
#include <QtWidgets/QMessageBox>

#include <SilkRoute/Users/usertable.h>

namespace Ui {
class LoginDialog;
}

typedef unsigned short ushort;

const ushort MAXLOG_ATTEMPTS = 3;

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    // not default constructor, could cause issues
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    
private slots:
    // WIll be called when login button is pressed
    void LoginBtnPressed(void);
    // Called when button 'Exit' is called
    void ExitBtnPressed(void);

private:
    // called constructor to avoid repetition
    void m_Construct(void);

    // class for table USER
    DB::UserTable userTable;

    // Generic encryption function
    const QString m_encrypt(const QString& val)
    {
        // Encrypt using sha1
        return QString(QCryptographicHash::hash((val.toLatin1()), QCryptographicHash::Sha1).toHex());
    }

    // Number of attempts to login, short to save space, attempts will only
    // reach the max number of >=3
    ushort m_loginAttempts;

    bool m_resized; // Store if item has already been resized

    const static QString TAG;

    Ui::LoginDialog* ui;
};

#endif // LOGINDIALOG_H
