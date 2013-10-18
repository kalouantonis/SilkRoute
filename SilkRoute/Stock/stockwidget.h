#ifndef STOCKWIDGET_H
#define STOCKWIDGET_H

#include <SilkRoute/Base/mdiwidget.h>

/*namespace Ui {
class StockWidget;
}*/

class StockWidget : public Base::MDIWidget
{
    Q_OBJECT
    
public:
    explicit StockWidget(QWidget *parent = 0);
    ~StockWidget();
    
private:
    //Ui::StockWidget *ui;
};

#endif // STOCKWIDGET_H
