#ifndef TYPESWIDGET_H
#define TYPESWIDGET_H

#include <SilkRoute/Base/mdiwidget.h>

const QString TypesObjectName = "TypesWidget";

class TypesWidget: public Base::MDIWidget
{
    Q_OBJECT

public:
    explicit TypesWidget(QWidget* parent = nullptr);
    ~TypesWidget();

    static const QString& objectName() { return TypesObjectName; }

public slots:
    virtual void add() final;

private slots:
    virtual void m_editAction(const QModelIndex& index) final;
};

#endif // TYPESWIDGET_H
