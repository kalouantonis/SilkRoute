#ifndef USERTABLE_H
#define USERTABLE_H

#include "itable.h"

// For encryption
#include <QCryptographicHash>

#include <QtCore>

// Result from successfull login, return a value for admin or
// normal user
enum USERTABLE_RETURN
{
    RES_NONE,
    RES_NORMUSER,
    RES_SUPERUSER,
    RES_FAILED
};

namespace DB
{
    // Handles USER table interactions
    class UserTable: public ITable
    {
    private:
       const QString m_encrypt(const QString& val);

       enum USER_COLS
       {
            ID,
           USERNAME,
           PASSWORD,
           ADMIN
       };

    public:
        // Default constructor
        UserTable(QObject* parent = 0);

        // Checks login details, returns true if login details are correct
        USERTABLE_RETURN IsValidLogin(const QString& username, const QString& password);
    };
}

#endif // USERTABLE_H
