#ifndef DATEFORMATDELEGATE_H
#define DATEFORMATDELEGATE_H

#include <QStyledItemDelegate>

/// Converts table item data to specified date format
class DateFormatDelegate: public QStyledItemDelegate
{
    Q_OBJECT

public:
    /// Constructor. Sets the required date format and caller as parent
    DateFormatDelegate(QString dateFormat, QObject* parent = 0);

    /// Called by framework when item text is requested
    virtual QString displayText(const QVariant &value, const QLocale &locale) const;

private:
    /// Date format used by delegate
    QString m_dateFormat;
};

#endif // DATEFORMATDELEGATE_H
