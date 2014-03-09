#include "plusminuspushwidget.h"

PlusMinusPushWidget::PlusMinusPushWidget(QWidget *parent) :
    QPushButton(parent)
    , m_bClicked(false)
{
    m_plusIcon.addFile(QString::fromUtf8(":general/Resources/images/add.png"));
    m_minusIcon.addFile(QString::fromUtf8(":general/Resources/images/remove.png"));

    this->setFlat(true);

    // Set default text to +
    //this->setText("+");
    this->setIcon(m_plusIcon);

    // Connect click to method
    this->connect(this, SIGNAL(clicked()), this, SLOT(m_pushClicked()));
}

void PlusMinusPushWidget::m_pushClicked()
{
    // Set text according to weather the button has been pressed
    //this->setText(m_bClicked ? "+" : "-");
    this->setIcon(m_bClicked ? m_plusIcon : m_minusIcon);
    // Set the clicked variable to the opposite of what it is now
    m_bClicked = !m_bClicked;
}
