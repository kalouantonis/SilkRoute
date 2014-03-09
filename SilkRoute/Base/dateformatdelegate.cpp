#include "dateformatdelegate.h"


#include <QDate>

DateFormatDelegate::DateFormatDelegate(QString dateFormat, QObject *parent)
    : QStyledItemDelegate(parent)   // Parent constructor
    , m_dateFormat(dateFormat)      // Initialize date format string
{
    // constructor
}

QString DateFormatDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    // We dont use the locale variable
    Q_UNUSED(locale);
    // Reformat string in to localized date format
    return QDate::fromString(value.toString(), m_dateFormat).toString();
}
