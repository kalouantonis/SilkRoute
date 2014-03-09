#ifndef PLUSMINUSPUSHWIDGET_H
#define PLUSMINUSPUSHWIDGET_H

#include <QPushButton>

class PlusMinusPushWidget : public QPushButton
{
    Q_OBJECT
public:
    /// constructor
    explicit PlusMinusPushWidget(QWidget *parent = 0);

    /// Getter for clicked variable
    bool isClicked() { return m_bClicked; }

private slots:
    /// Event that button is clicked
    void m_pushClicked();

private:
    /// Has the button been clicked
    bool m_bClicked;

    /// Icon to represent plus symbol
    QIcon m_plusIcon;
    /// Icon to represent minus symbol
    QIcon m_minusIcon;
};

#endif // PLUSMINUSPUSHWIDGET_H
