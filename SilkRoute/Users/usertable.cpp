#include "usertable.h"

// For queries
#include <QSqlQuery>

namespace DB
{
    UserTable::UserTable(QObject* parent)
        : ITable(parent)
    {
    }

    const QString UserTable::m_encrypt(const QString &val)
    {
        // Use SHA1 as no current exploits are known for it
        // unlike MD5
        return QString(QCryptographicHash::hash(val.toAscii(), QCryptographicHash::Sha1).toHex());
    }

    USERTABLE_RETURN UserTable::IsValidLogin(const QString &username, const QString &password)
    {
        // Clear previous query
        m_ClearQuery();

        m_qry.prepare("SELECT admin FROM users WHERE username = :user AND password = :pass");

        // Encrypt input values, never decrypt db values,
        // that would leave security holes
        m_qry.bindValue(":user", m_encrypt(username));
        m_qry.bindValue(":password", m_encrypt(password));

        if(!m_qry.exec())
        {
            // Query failed, TODO: Better handeling, maybe throw exception
#ifdef _DEBUG
            qDebug() << "Failed to grab user and password credentials";
#endif
           return RES_FAILED;
        }

        if(m_qry.next())
        {
            // Get the admin value
            int admin = m_qry.value(0).toInt();

            // Admin == 1
            if(admin)
                return RES_SUPERUSER;

            return RES_NORMUSER;
        }

        return RES_NONE;
    }
}
