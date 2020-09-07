#include "../headers/pushbutton.h"

PushButton::PushButton(QWidget *parent, TableWindow *t, int mode)
    : QPushButton(parent), t(t)
{
    if( mode == 0 )
    {
        this->setText("Add new patient");
        this->move(0, 100);
        this->setFixedSize(QSize(150, 25));
        connect(this, SIGNAL (released()), parent, SLOT (handleAddButton()));
    }

    else
    {
        this->setText("Delete patient");
        this->move(135, 100);
        this->setFixedSize(QSize(150, 25));
        connect(this, SIGNAL (released()), parent, SLOT (handleDeleteButton()));
    }
}









