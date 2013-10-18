#include "stockwidget.h"
#include "ui_stockwidget.h"

StockWidget::StockWidget(QWidget *parent) :
    Base::MDIWidget(parent)
    //ui(new Ui::StockWidget)
{
    //ui->setupUi(this);
    this->setWindowTitle("Stock");
}

StockWidget::~StockWidget()
{
    //delete ui;
}
