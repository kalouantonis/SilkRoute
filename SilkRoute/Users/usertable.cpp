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
        return QString(QCryptographicHash::hash(val.toLatin1(), QCryptographicHash::Sha1).toHex());
    }

    USERTABLE_RETURN UserTable::IsValidLogin(const QString &username, const QString &password)
    {
        // Clear previous query
        m_ClearQuery();

        m_qry.prepare("SELECT id FROM users WHERE username = :user AND password = :pass AND deleted=0");

        // Encrypt input values, never decrypt db values,
        // that would leave security holes
        m_qry.bindValue(":user", m_encrypt(username));
        m_qry.bindValue(":password", m_encrypt(password));

        if(!m_qry.exec())
        {
#ifdef _DEBUG
            qDebug() << "Failed to grab user and password credentials";
#endif
           return RES_FAILED;
        }

        if(m_qry.next())
        {
            return RES_SUCCESS;
        }

        return RES_NONE;
    }
}
