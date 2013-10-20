#include "stockwidget.h"
//#include "ui_stockwidget.h"

StockWidget::StockWidget(QWidget *parent) :
    Base::MDIWidget(parent)
{
    this->setWindowTitle("Stock");

    //QIcon winIcon;
    //winIcon.addFile(tr(":"));
}

StockWidget::~StockWidget()
{
}
