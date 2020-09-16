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
    ActionStore() = delete;
    static void addAction( ActionID id, QAction* action );
    static QAction* action( ActionID id );
private:
    static QMap<ActionID, QAction*> m_actions;
};

#endif // ACTIONSTORE_H
