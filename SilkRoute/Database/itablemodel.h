#ifndef ITABLEMODEL_H
#define ITABLEMODEL_H

#include <QSqlQueryModel>

namespace DB
{

class ITableModel: public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit ITableModel(QObject* parent = 0);
    virtual ~ITableModel() {}

    // Select all items from table
    virtual void SelectAll() = 0;

    // Search for item
    virtual void Search(const QString& term) = 0;

    const QString GetLastError();

signals:
    void dataChanged();

private slots:
    void updateAllData() { this->SelectAll(); }
};

}

#endif // ITABLEMODEL_H
