from PyQt4.QtSql import *
from PyQt4.QtCore import QString, QCryptographicHash, QByteArray
import sys

class DBConnection:
    __filename = ""

    def __init__(self):
        # Set driver
        self.__dbcon = QSqlDatabase.addDatabase("QSQLITE")
        
    def connect(self, filename):
        self.__filename = filename

        self.__dbcon.setDatabaseName(filename)
        
        if not self.__dbcon.open():
            # Throw exception
            raise RuntimeError("Could not connect to database: " + str(self.__dbcon.lastError))

        print "Connection made successfully"
        
    def close(self):
        self.__dbcon.close()

        print "Connection has closed"

    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        self.close()

class TableManip:
    __tablename = ""

    def __init__(self, tablename):
        self.__tablename = tablename

    """
    Should provide args like this:
    id="INTEGER", name="TEXT"
    """
    """
    def createTable(**kwargs):
        query = QSqlQuery()

        queryString = "CREATE TABLE IF NOT EXISTS " + self.__tablename

        for (ident, typename) in zip(kwargs.keys(), kwargs.values()):
        queryString += key + 
        """

    def Insert(self, **kwargs):
        query_string = "INSERT INTO " + self.__tablename 
        query_keys = "("
        query_vals = "("

        for index, (key, value) in enumerate(zip(kwargs.keys(), kwargs.values())):
            query_keys += '`' + key + '`'

            query_vals += self.__checktype(value)

            query_keys += self.__appendcomma(index, len(kwargs))
            query_vals += self.__appendcomma(index, len(kwargs))

        query_string += query_keys + ") VALUES " + query_vals + ")"

        print "Performing query"
        print "\n\t" + query_string

        query = QSqlQuery()
        query.prepare(query_string)

        if not query.exec_():
            raise RuntimeError("Query failed: " + str(query.lastError().text()))


    def __checktype(self, value):
        if (type(value) is str) or (type(value) is unicode) or (type(value) is chr):
            return "\"" + value + "\""

        return str(value)

    def __appendcomma(self, index, size):
        if index != (size - 1):
            return ", "

        return ''

def Encrypt(val):
    return QString(QCryptographicHash.hash(val, QCryptographicHash.Sha1).toHex())

def GenerateUsers():
    table = TableManip("users")

    table.Insert(username=Encrypt("antonis"), password=Encrypt("wordpass"), admin=0)

if __name__ == '__main__':
    con = DBConnection()

    #Get cmd line args
    (scriptname, filename) = sys.argv

    con.connect(filename)

    GenerateUsers()
