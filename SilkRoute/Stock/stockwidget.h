#ifndef STOCKWIDGET_H
#define STOCKWIDGET_H

#include <SilkRoute/Base/mdiwidget.h>

class StockWidget : public Base::MDIWidget
{
    Q_OBJECT
    
public:
    explicit StockWidget(QWidget *parent = 0);
    ~StockWidget();
    
private:
};

#endif // STOCKWIDGET_H
