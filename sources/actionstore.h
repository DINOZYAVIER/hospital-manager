#ifndef ACTIONSTORE_H
#define ACTIONSTORE_H

#include <QAction>
#include <QMap>

typedef enum {
    aAddPatient,
    aRemovePatient,
    aAddRecord,
    aRemoveRecord,
    aAddRadiograph,
    aRemoveRadiograph,
    aNextRadiograph,
    aPrevRadiograph
} ActionID;

class ActionStore
{
public:

    static ActionStore& get_instance() { static ActionStore as; return as; }
    void addAction( ActionID id, QAction* action );
    QAction* action( ActionID id ) const;
protected:
    ActionStore() { }
    ActionStore& operator=( ActionStore& );
    ~ActionStore() { }
private:
       QMap<ActionID, QAction*> m_actions;
};

#endif // ACTIONSTORE_H
