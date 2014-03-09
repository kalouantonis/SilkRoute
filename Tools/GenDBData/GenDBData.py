#!/usr/bin/env python3

import sys
from PyQt5.QtCore import QCryptographicHash
from PyQt5.QtSql import QSqlDatabase, QSqlQuery, QSqlError

class DBConnector:
    def __init__(self):
        self.db = QSqlDatabase.addDatabase("QSQLITE")

    def connect(self, filename):
        if self.db.isOpen():
            print("Already connected to database", file=sys.stdout)

            return False

        self.db.setDatabaseName(filename)

        if self.db.open() is False:
            print ("Connection to " + filename + " failed", file=sys.stderr)

            return False

        print ("Connection to " + filename + " succeeded", file=sys.stdout)

        return True



def Encrypt(val):
    return str((QCryptographicHash.hash(val.encode("latin-1"), QCryptographicHash.Sha1).toHex()))


def CreateUser(username, password):
    qry = QSqlQuery()

    qry.prepare("""INSERT INTO users (username, password, deleted)
        VALUES (:username, :password,  0)""")

    qry.bindValue(":username", Encrypt(username))
    qry.bindValue(":password", Encrypt(password))

    if qry.exec_() is False:
        print("Query failed in users table\n\t" + qry.lastError().text(), file=sys.stderr)

        return False

    print( "Query to users table succeeded", file=sys.stdout)

    return True


if __name__ == '__main__':
    if len(sys.argv) < 4:
        print("Usage: GenDBData <filename> <username> <password>", file=sys.stderr)

    (script, filename, username, password) = sys.argv

    db = DBConnector()
    db.connect(filename)

    CreateUser(username, password)

