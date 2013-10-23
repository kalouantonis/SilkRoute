#include "stockwidget.h"
//#include "ui_stockwidget.h"

StockWidget::StockWidget(QWidget *parent) :
    Base::MDIWidget(parent)
{
    // Set object name for easier recognition by parent classes
    this->setObjectName(StockObjectName);

    this->setWindowTitle(tr("Stock"));

    QIcon winIcon;
    winIcon.addFile(QString::fromUtf8(":stock/Resources/images/stock-view.png"), QSize(), QIcon::Normal, QIcon::On);
    this->setWindowIcon(winIcon);
}

StockWidget::~StockWidget()
{
}
