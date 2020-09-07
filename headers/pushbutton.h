#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "../headers/tablewindow.h"
#include <QPushButton>
#include <QWidget>

class PushButton : public QPushButton
{
public:
    PushButton(QWidget *parent, TableWindow *t, int mode);

    void addClicked();



private:
    TableWindow *t;
};

#endif // PUSHBUTTON_H
