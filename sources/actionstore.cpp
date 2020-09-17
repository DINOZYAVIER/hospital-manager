#include "precompiled.h"
#include "actionstore.h"

QMap<ActionID, QAction*> ActionStore::m_actions = QMap<ActionID, QAction*>();

void ActionStore::addAction( ActionID id, QAction * action )
{
    m_actions[ id ] = action;
}

QAction* ActionStore::action( ActionID id )
{
    Q_ASSERT( m_actions.contains( id ) );
    return m_actions.value( id );
}

