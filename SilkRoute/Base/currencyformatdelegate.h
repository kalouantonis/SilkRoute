#ifndef CURRENCYFORMATDELEGATE_H
#define CURRENCYFORMATDELEGATE_H

#include <QStyledItemDelegate>

/// Shows table item data in localized currency format
class CurrencyFormatDelegate: public QStyledItemDelegate
{
    Q_OBJECT

public:
    /// Constructor, takes parent caller as argument
    CurrencyFormatDelegate(QObject* parent = nullptr);

    /// Called by framework when text is requested
    virtual QString displayText(const QVariant &value, const QLocale &locale) const;
};

#endif // CURRENCYFORMATDELEGATE_H
