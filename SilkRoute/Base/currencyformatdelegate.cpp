#include "currencyformatdelegate.h"

CurrencyFormatDelegate::CurrencyFormatDelegate(QObject *parent)
    : QStyledItemDelegate(parent) // Call parent constructor
{
}

QString CurrencyFormatDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    // Format text to localized currency format
    return locale.toCurrencyString(value.toDouble());
}
